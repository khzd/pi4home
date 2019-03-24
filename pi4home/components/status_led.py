import voluptuous as vol

from pi4home import config_validation as cv, pins
from pi4home.const import CONF_ID, CONF_PIN
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import gpio_output_pin_expression, setup_component
from pi4home.cpp_types import App, Component, pi4home_ns

StatusLEDComponent = pi4home_ns.class_('StatusLEDComponent', Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_variable_id(StatusLEDComponent),
    vol.Optional(CONF_PIN): pins.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    for pin in gpio_output_pin_expression(config[CONF_PIN]):
        yield
    rhs = App.make_status_led(pin)
    var = Pvariable(config[CONF_ID], rhs)

    setup_component(var, config)


BUILD_FLAGS = '-DUSE_STATUS_LED'
