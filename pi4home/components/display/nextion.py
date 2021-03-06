from pi4home.components import display, uart
from pi4home.components.uart import UARTComponent
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_LAMBDA, CONF_UART_ID
from pi4home.cpp_generator import Pvariable, add, get_variable, process_lambda
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, PollingComponent, void

DEPENDENCIES = ['uart']

Nextion = display.display_ns.class_('Nextion', PollingComponent, uart.UARTDevice)
NextionRef = Nextion.operator('ref')

PLATFORM_SCHEMA = display.BASIC_DISPLAY_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(Nextion),
    cv.GenerateID(CONF_UART_ID): cv.use_variable_id(UARTComponent),
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    for uart_ in get_variable(config[CONF_UART_ID]):
        yield
    rhs = App.make_nextion(uart_)
    nextion = Pvariable(config[CONF_ID], rhs)

    if CONF_LAMBDA in config:
        for lambda_ in process_lambda(config[CONF_LAMBDA], [(NextionRef, 'it')],
                                      return_type=void):
            yield
        add(nextion.set_writer(lambda_))

    display.setup_display(nextion, config)
    setup_component(nextion, config)


BUILD_FLAGS = '-DUSE_NEXTION'
