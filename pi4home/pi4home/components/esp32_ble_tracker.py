import voluptuous as vol

from pi4home import config_validation as cv
from pi4home.components import sensor
from pi4home.const import CONF_ID, CONF_SCAN_INTERVAL, ESP_PLATFORM_ESP32
from pi4home.core import HexInt
from pi4home.cpp_generator import Pvariable, add
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Component, pi4home_ns

ESP_PLATFORMS = [ESP_PLATFORM_ESP32]

CONF_ESP32_BLE_ID = 'esp32_ble_id'
ESP32BLETracker = pi4home_ns.class_('ESP32BLETracker', Component)
XiaomiSensor = pi4home_ns.class_('XiaomiSensor', sensor.Sensor)
XiaomiDevice = pi4home_ns.class_('XiaomiDevice')
XIAOMI_SENSOR_SCHEMA = sensor.SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(XiaomiSensor)
})

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_variable_id(ESP32BLETracker),
    vol.Optional(CONF_SCAN_INTERVAL): cv.positive_time_period_seconds,
}).extend(cv.COMPONENT_SCHEMA.schema)


def make_address_array(address):
    return [HexInt(i) for i in address.parts]


def to_code(config):
    rhs = App.make_esp32_ble_tracker()
    ble = Pvariable(config[CONF_ID], rhs)
    if CONF_SCAN_INTERVAL in config:
        add(ble.set_scan_interval(config[CONF_SCAN_INTERVAL]))

    setup_component(ble, config)


BUILD_FLAGS = '-DUSE_ESP32_BLE_TRACKER'
