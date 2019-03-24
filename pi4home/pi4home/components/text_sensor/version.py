from pi4home.components import text_sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_NAME
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Component

VersionTextSensor = text_sensor.text_sensor_ns.class_('VersionTextSensor',
                                                      text_sensor.TextSensor, Component)

PLATFORM_SCHEMA = cv.nameable(text_sensor.TEXT_SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(VersionTextSensor),
}).extend(cv.COMPONENT_SCHEMA.schema))


def to_code(config):
    rhs = App.make_version_text_sensor(config[CONF_NAME])
    sens = Pvariable(config[CONF_ID], rhs)
    text_sensor.setup_text_sensor(sens, config)
    setup_component(sens, config)


BUILD_FLAGS = '-DUSE_VERSION_TEXT_SENSOR'
