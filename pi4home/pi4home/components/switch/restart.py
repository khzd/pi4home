import voluptuous as vol

from pi4home.components import switch
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_INVERTED, CONF_NAME
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_types import App

RestartSwitch = switch.switch_ns.class_('RestartSwitch', switch.Switch)

PLATFORM_SCHEMA = cv.nameable(switch.SWITCH_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(RestartSwitch),
    vol.Optional(CONF_INVERTED): cv.invalid("Restart switches do not support inverted mode!"),
}))


def to_code(config):
    rhs = App.make_restart_switch(config[CONF_NAME])
    restart = Pvariable(config[CONF_ID], rhs)
    switch.setup_switch(restart, config)


BUILD_FLAGS = '-DUSE_RESTART_SWITCH'
