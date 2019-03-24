import voluptuous as vol

from pi4home import pins
from pi4home.components import sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_NAME, CONF_PIN, CONF_UPDATE_INTERVAL
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import gpio_input_pin_expression, setup_component
from pi4home.cpp_types import App

DutyCycleSensor = sensor.sensor_ns.class_('DutyCycleSensor', sensor.PollingSensorComponent)

PLATFORM_SCHEMA = cv.nameable(sensor.SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(DutyCycleSensor),
    vol.Required(CONF_PIN): vol.All(pins.internal_gpio_input_pin_schema,
                                    pins.validate_has_interrupt),
    vol.Optional(CONF_UPDATE_INTERVAL): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA.schema))


def to_code(config):
    for pin in gpio_input_pin_expression(config[CONF_PIN]):
        yield
    rhs = App.make_duty_cycle_sensor(config[CONF_NAME], pin,
                                     config.get(CONF_UPDATE_INTERVAL))
    duty = Pvariable(config[CONF_ID], rhs)
    sensor.setup_sensor(duty, config)
    setup_component(duty, config)


BUILD_FLAGS = '-DUSE_DUTY_CYCLE_SENSOR'
