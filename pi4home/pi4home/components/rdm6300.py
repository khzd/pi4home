from pi4home.components import binary_sensor, uart
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_UART_ID
from pi4home.cpp_generator import Pvariable, get_variable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Component

DEPENDENCIES = ['uart']

RDM6300Component = binary_sensor.binary_sensor_ns.class_('RDM6300Component', Component,
                                                         uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_variable_id(RDM6300Component),
    cv.GenerateID(CONF_UART_ID): cv.use_variable_id(uart.UARTComponent),
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    for uart_ in get_variable(config[CONF_UART_ID]):
        yield
    rhs = App.make_rdm6300_component(uart_)
    var = Pvariable(config[CONF_ID], rhs)
    setup_component(var, config)


BUILD_FLAGS = '-DUSE_RDM6300'
