import voluptuous as vol

from pi4home import pins
import pi4home.config_validation as cv
from pi4home.const import CONF_ADDRESS, CONF_ID
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, GPIOInputPin, GPIOOutputPin, io_ns, pi4home_ns

DEPENDENCIES = ['i2c']
MULTI_CONF = True

MCP23017GPIOMode = pi4home_ns.enum('MCP23017GPIOMode')
MCP23017_GPIO_MODES = {
    'INPUT': MCP23017GPIOMode.MCP23017_INPUT,
    'INPUT_PULLUP': MCP23017GPIOMode.MCP23017_INPUT_PULLUP,
    'OUTPUT': MCP23017GPIOMode.MCP23017_OUTPUT,
}

MCP23017GPIOInputPin = io_ns.class_('MCP23017GPIOInputPin', GPIOInputPin)
MCP23017GPIOOutputPin = io_ns.class_('MCP23017GPIOOutputPin', GPIOOutputPin)

CONFIG_SCHEMA = cv.Schema({
    vol.Required(CONF_ID): cv.declare_variable_id(pins.MCP23017),
    vol.Optional(CONF_ADDRESS, default=0x20): cv.i2c_address,
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    rhs = App.make_mcp23017_component(config[CONF_ADDRESS])
    var = Pvariable(config[CONF_ID], rhs)
    setup_component(var, config)


BUILD_FLAGS = '-DUSE_MCP23017'
