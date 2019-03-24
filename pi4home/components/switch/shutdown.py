import voluptuous as vol

from pi4home.components import switch
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_INVERTED, CONF_NAME
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_types import App

ShutdownSwitch = switch.switch_ns.class_('ShutdownSwitch', switch.Switch)

PLATFORM_SCHEMA = cv.nameable(switch.SWITCH_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(ShutdownSwitch),
    vol.Optional(CONF_INVERTED): cv.invalid("Shutdown switches do not support inverted mode!"),
}))


def to_code(config):
    rhs = App.make_shutdown_switch(config[CONF_NAME])
    shutdown = Pvariable(config[CONF_ID], rhs)
    switch.setup_switch(shutdown, config)


BUILD_FLAGS = '-DUSE_SHUTDOWN_SWITCH'
