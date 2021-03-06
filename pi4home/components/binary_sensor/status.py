from pi4home.components import binary_sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_NAME
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Component

StatusBinarySensor = binary_sensor.binary_sensor_ns.class_('StatusBinarySensor',
                                                           binary_sensor.BinarySensor,
                                                           Component)

PLATFORM_SCHEMA = cv.nameable(binary_sensor.BINARY_SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(StatusBinarySensor),
}).extend(cv.COMPONENT_SCHEMA.schema))


def to_code(config):
    rhs = App.make_status_binary_sensor(config[CONF_NAME])
    status = Pvariable(config[CONF_ID], rhs)
    binary_sensor.setup_binary_sensor(status, config)
    setup_component(status, config)


BUILD_FLAGS = '-DUSE_STATUS_BINARY_SENSOR'
