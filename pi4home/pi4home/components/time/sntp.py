import voluptuous as vol

from pi4home.components import time as time_
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_SERVERS
from pi4home.cpp_generator import Pvariable, add
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App

SNTPComponent = time_.time_ns.class_('SNTPComponent', time_.RealTimeClockComponent)

PLATFORM_SCHEMA = time_.TIME_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(SNTPComponent),
    vol.Optional(CONF_SERVERS): vol.All(cv.ensure_list(cv.domain), vol.Length(min=1, max=3)),
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    rhs = App.make_sntp_component()
    sntp = Pvariable(config[CONF_ID], rhs)
    if CONF_SERVERS in config:
        servers = config[CONF_SERVERS]
        servers += [''] * (3 - len(servers))
        add(sntp.set_servers(*servers))

    time_.setup_time(sntp, config)
    setup_component(sntp, config)


BUILD_FLAGS = '-DUSE_SNTP_COMPONENT'
