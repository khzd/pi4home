from datetime import datetime
import functools
import logging
import socket
import threading
import time

# pylint: disable=unused-import
from typing import Optional  # noqa
from google.protobuf import message  # noqa

from pi4home import const
import pi4home.api.api_pb2 as pb
from pi4home.const import CONF_PASSWORD, CONF_PORT
from pi4home.core import pi4homeError
from pi4home.helpers import resolve_ip_address, indent, color
from pi4home.py_compat import text_type, IS_PY2, byte_to_bytes, char_to_byte, format_bytes
from pi4home.util import safe_print

_LOGGER = logging.getLogger(__name__)


class APIConnectionError(pi4homeError):
    pass


MESSAGE_TYPE_TO_PROTO = {
    1: pb.HelloRequest,
    2: pb.HelloResponse,
    3: pb.ConnectRequest,
    4: pb.ConnectResponse,
    5: pb.DisconnectRequest,
    6: pb.DisconnectResponse,
    7: pb.PingRequest,
    8: pb.PingResponse,
    9: pb.DeviceInfoRequest,
    10: pb.DeviceInfoResponse,
    11: pb.ListEntitiesRequest,
    12: pb.ListEntitiesBinarySensorResponse,
    13: pb.ListEntitiesCoverResponse,
    14: pb.ListEntitiesFanResponse,
    15: pb.ListEntitiesLightResponse,
    16: pb.ListEntitiesSensorResponse,
    17: pb.ListEntitiesSwitchResponse,
    18: pb.ListEntitiesTextSensorResponse,
    19: pb.ListEntitiesDoneResponse,
    20: pb.SubscribeStatesRequest,
    21: pb.BinarySensorStateResponse,
    22: pb.CoverStateResponse,
    23: pb.FanStateResponse,
    24: pb.LightStateResponse,
    25: pb.SensorStateResponse,
    26: pb.SwitchStateResponse,
    27: pb.TextSensorStateResponse,
    28: pb.SubscribeLogsRequest,
    29: pb.SubscribeLogsResponse,
    30: pb.CoverCommandRequest,
    31: pb.FanCommandRequest,
    32: pb.LightCommandRequest,
    33: pb.SwitchCommandRequest,
    34: pb.SubscribeServiceCallsRequest,
    35: pb.ServiceCallResponse,
    36: pb.GetTimeRequest,
    37: pb.GetTimeResponse,
}


def _varuint_to_bytes(value):
    if value <= 0x7F:
        return byte_to_bytes(value)

    ret = bytes()
    while value:
        temp = value & 0x7F
        value >>= 7
        if value:
            ret += byte_to_bytes(temp | 0x80)
        else:
            ret += byte_to_bytes(temp)

    return ret


def _bytes_to_varuint(value):
    result = 0
    bitpos = 0
    for c in value:
        val = char_to_byte(c)
        result |= (val & 0x7F) << bitpos
        bitpos += 7
        if (val & 0x80) == 0:
            return result
    return None


# pylint: disable=too-many-instance-attributes,not-callable
class APIClient(threading.Thread):
    def __init__(self, address, port, password):
        threading.Thread.__init__(self)
        self._address = address  # type: str
        self._port = port  # type: int
        self._password = password  # type: Optional[str]
        self._socket = None  # type: Optional[socket.socket]
        self._socket_open_event = threading.Event()
        self._socket_write_lock = threading.Lock()
        self._connected = False
        self._authenticated = False
        self._message_handlers = []
        self._keepalive = 5
        self._ping_timer = None
        self._refresh_ping()

        self.on_disconnect = None
        self.on_connect = None
        self.on_login = None
        self.auto_reconnect = False
        self._running_event = threading.Event()
        self._stop_event = threading.Event()

    @property
    def stopped(self):
        return self._stop_event.is_set()

    def _refresh_ping(self):
        if self._ping_timer is not None:
            self._ping_timer.cancel()
            self._ping_timer = None

        def func():
            self._ping_timer = None

            if self._connected:
                try:
                    self.ping()
                except APIConnectionError:
                    self._fatal_error()
                else:
                    self._refresh_ping()

        self._ping_timer = threading.Timer(self._keepalive, func)
        self._ping_timer.start()

    def _cancel_ping(self):
        if self._ping_timer is not None:
            self._ping_timer.cancel()
            self._ping_timer = None

    def _close_socket(self):
        self._cancel_ping()
        if self._socket is not None:
            self._socket.close()
            self._socket = None
        self._socket_open_event.clear()
        self._connected = False
        self._authenticated = False
        self._message_handlers = []

    def stop(self, force=False):
        if self.stopped:
            raise ValueError

        if self._connected and not force:
            try:
                self.disconnect()
            except APIConnectionError:
                pass
        self._close_socket()

        self._stop_event.set()
        if not force:
            self.join()

    def connect(self):
        if not self._running_event.wait(0.1):
            raise APIConnectionError("You need to call start() first!")

        if self._connected:
            raise APIConnectionError("Already connected!")

        try:
            ip = resolve_ip_address(self._address)
        except pi4homeError as err:
            _LOGGER.warning("Error resolving IP address of %s. Is it connected to WiFi?",
                            self._address)
            _LOGGER.warning("(If this error persists, please set a static IP address: "
                            "https://github.com/khzd/pi4home/components/wifi.html#manual-ips)")
            raise APIConnectionError(err)

        _LOGGER.info("Connecting to %s:%s (%s)", self._address, self._port, ip)
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._socket.settimeout(10.0)
        self._socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        try:
            self._socket.connect((ip, self._port))
        except socket.error as err:
            self._fatal_error()
            raise APIConnectionError("Error connecting to {}: {}".format(ip, err))
        self._socket.settimeout(0.1)

        self._socket_open_event.set()

        hello = pb.HelloRequest()
        hello.client_info = 'PI4Home v{}'.format(const.__version__)
        try:
            resp = self._send_message_await_response(hello, pb.HelloResponse)
        except APIConnectionError as err:
            self._fatal_error()
            raise err
        _LOGGER.debug("Successfully connected to %s ('%s' API=%s.%s)", self._address,
                      resp.server_info, resp.api_version_major, resp.api_version_minor)
        self._connected = True
        if self.on_connect is not None:
            self.on_connect()

    def _check_connected(self):
        if not self._connected:
            self._fatal_error()
            raise APIConnectionError("Must be connected!")

    def login(self):
        self._check_connected()
        if self._authenticated:
            raise APIConnectionError("Already logged in!")

        connect = pb.ConnectRequest()
        if self._password is not None:
            connect.password = self._password
        resp = self._send_message_await_response(connect, pb.ConnectResponse)
        if resp.invalid_password:
            raise APIConnectionError("Invalid password!")

        self._authenticated = True
        if self.on_login is not None:
            self.on_login()

    def _fatal_error(self):
        was_connected = self._connected

        self._close_socket()

        if was_connected and self.on_disconnect is not None:
            self.on_disconnect()

    def _write(self, data):  # type: (bytes) -> None
        if self._socket is None:
            raise APIConnectionError("Socket closed")

        _LOGGER.debug("Write: %s", format_bytes(data))
        with self._socket_write_lock:
            try:
                self._socket.sendall(data)
            except socket.error as err:
                self._fatal_error()
                raise APIConnectionError("Error while writing data: {}".format(err))

    def _send_message(self, msg):
        # type: (message.Message) -> None
        for message_type, klass in MESSAGE_TYPE_TO_PROTO.items():
            if isinstance(msg, klass):
                break
        else:
            raise ValueError

        encoded = msg.SerializeToString()
        _LOGGER.debug("Sending %s:\n%s", type(msg), indent(text_type(msg)))
        if IS_PY2:
            req = chr(0x00)
        else:
            req = bytes([0])
        req += _varuint_to_bytes(len(encoded))
        req += _varuint_to_bytes(message_type)
        req += encoded
        self._write(req)
        self._refresh_ping()

    def _send_message_await_response_complex(self, send_msg, do_append, do_stop, timeout=1):
        event = threading.Event()
        responses = []

        def on_message(resp):
            if do_append(resp):
                responses.append(resp)
            if do_stop(resp):
                event.set()

        self._message_handlers.append(on_message)
        self._send_message(send_msg)
        ret = event.wait(timeout)
        try:
            self._message_handlers.remove(on_message)
        except ValueError:
            pass
        if not ret:
            raise APIConnectionError("Timeout while waiting for message response!")
        return responses

    def _send_message_await_response(self, send_msg, response_type, timeout=1):
        def is_response(msg):
            return isinstance(msg, response_type)

        return self._send_message_await_response_complex(send_msg, is_response, is_response,
                                                         timeout)[0]

    def device_info(self):
        self._check_connected()
        return self._send_message_await_response(pb.DeviceInfoRequest(), pb.DeviceInfoResponse)

    def ping(self):
        self._check_connected()
        return self._send_message_await_response(pb.PingRequest(), pb.PingResponse)

    def disconnect(self):
        self._check_connected()

        try:
            self._send_message_await_response(pb.DisconnectRequest(), pb.DisconnectResponse)
        except APIConnectionError:
            pass
        self._close_socket()

        if self.on_disconnect is not None:
            self.on_disconnect()

    def _check_authenticated(self):
        if not self._authenticated:
            raise APIConnectionError("Must login first!")

    def subscribe_logs(self, on_log, log_level=None, dump_config=False):
        self._check_authenticated()

        def on_msg(msg):
            if isinstance(msg, pb.SubscribeLogsResponse):
                on_log(msg)

        self._message_handlers.append(on_msg)
        req = pb.SubscribeLogsRequest(dump_config=dump_config)
        if log_level is not None:
            req.level = log_level
        self._send_message(req)

    def _recv(self, amount):
        ret = bytes()
        if amount == 0:
            return ret

        while len(ret) < amount:
            if self.stopped:
                raise APIConnectionError("Stopped!")
            if not self._socket_open_event.is_set():
                raise APIConnectionError("No socket!")
            try:
                val = self._socket.recv(amount - len(ret))
            except AttributeError:
                raise APIConnectionError("Socket was closed")
            except socket.timeout:
                continue
            except socket.error as err:
                raise APIConnectionError("Error while receiving data: {}".format(err))
            ret += val
        return ret

    def _recv_varint(self):
        raw = bytes()
        while not raw or char_to_byte(raw[-1]) & 0x80:
            raw += self._recv(1)
        return _bytes_to_varuint(raw)

    def _run_once(self):
        if not self._socket_open_event.wait(0.1):
            return

        # Preamble
        if char_to_byte(self._recv(1)[0]) != 0x00:
            raise APIConnectionError("Invalid preamble")

        length = self._recv_varint()
        msg_type = self._recv_varint()

        raw_msg = self._recv(length)
        if msg_type not in MESSAGE_TYPE_TO_PROTO:
            _LOGGER.debug("Skipping message type %s", msg_type)
            return

        msg = MESSAGE_TYPE_TO_PROTO[msg_type]()
        msg.ParseFromString(raw_msg)
        _LOGGER.debug("Got message: %s:\n%s", type(msg), indent(str(msg)))
        for msg_handler in self._message_handlers[:]:
            msg_handler(msg)
        self._handle_internal_messages(msg)
        self._refresh_ping()

    def run(self):
        self._running_event.set()
        while not self.stopped:
            try:
                self._run_once()
            except APIConnectionError as err:
                if self.stopped:
                    break
                if self._connected:
                    _LOGGER.error("Error while reading incoming messages: %s", err)
                    self._fatal_error()
        self._running_event.clear()

    def _handle_internal_messages(self, msg):
        if isinstance(msg, pb.DisconnectRequest):
            self._send_message(pb.DisconnectResponse())
            if self._socket is not None:
                self._socket.close()
                self._socket = None
            self._connected = False
            if self.on_disconnect is not None:
                self.on_disconnect()
        elif isinstance(msg, pb.PingRequest):
            self._send_message(pb.PingResponse())
        elif isinstance(msg, pb.GetTimeRequest):
            resp = pb.GetTimeResponse()
            resp.epoch_seconds = int(time.time())
            self._send_message(resp)


def run_logs(config, address):
    conf = config['api']
    port = conf[CONF_PORT]
    password = conf[CONF_PASSWORD]
    _LOGGER.info("Starting log output from %s using pi4home API", address)

    cli = APIClient(address, port, password)
    stopping = False
    retry_timer = []

    has_connects = []

    def try_connect(tries=0, is_disconnect=True):
        if stopping:
            return

        if is_disconnect:
            _LOGGER.warning(u"Disconnected from API.")

        while retry_timer:
            retry_timer.pop(0).cancel()

        error = None
        try:
            cli.connect()
            cli.login()
        except APIConnectionError as err:  # noqa
            error = err

        if error is None:
            _LOGGER.info("Successfully connected to %s", address)
            return

        wait_time = min(2**tries, 300)
        if not has_connects:
            _LOGGER.warning(u"Initial connection failed. The ESP might not be connected "
                            u"to WiFi yet (%s). Re-Trying in %s seconds",
                            error, wait_time)
        else:
            _LOGGER.warning(u"Couldn't connect to API (%s). Trying to reconnect in %s seconds",
                            error, wait_time)
        timer = threading.Timer(wait_time, functools.partial(try_connect, tries + 1, is_disconnect))
        timer.start()
        retry_timer.append(timer)

    def on_log(msg):
        time_ = datetime.now().time().strftime(u'[%H:%M:%S]')
        text = msg.message
        if msg.send_failed:
            text = color('white', '(Message skipped because it was too big to fit in '
                                  'TCP buffer - This is only cosmetic)')
        safe_print(time_ + text)

    def on_login():
        try:
            cli.subscribe_logs(on_log, dump_config=not has_connects)
            has_connects.append(True)
        except APIConnectionError:
            cli.disconnect()

    cli.on_disconnect = try_connect
    cli.on_login = on_login
    cli.start()

    try:
        try_connect(is_disconnect=False)
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        stopping = True
        cli.stop(True)
        while retry_timer:
            retry_timer.pop(0).cancel()
    return 0
