import voluptuous as vol

from pi4home.components import text_sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_LAMBDA, CONF_NAME, CONF_TEXT_SENSORS
from pi4home.cpp_generator import add, process_lambda, variable
from pi4home.cpp_types import std_vector

CustomTextSensorConstructor = text_sensor.text_sensor_ns.class_('CustomTextSensorConstructor')

PLATFORM_SCHEMA = text_sensor.PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(CustomTextSensorConstructor),
    vol.Required(CONF_LAMBDA): cv.lambda_,
    vol.Required(CONF_TEXT_SENSORS):
        cv.ensure_list(text_sensor.TEXT_SENSOR_SCHEMA.extend({
            cv.GenerateID(): cv.declare_variable_id(text_sensor.TextSensor),
        })),
})


def to_code(config):
    for template_ in process_lambda(config[CONF_LAMBDA], [],
                                    return_type=std_vector.template(text_sensor.TextSensorPtr)):
        yield

    rhs = CustomTextSensorConstructor(template_)
    custom = variable(config[CONF_ID], rhs)
    for i, conf in enumerate(config[CONF_TEXT_SENSORS]):
        rhs = custom.Pget_text_sensor(i)
        add(rhs.set_name(conf[CONF_NAME]))
        text_sensor.register_text_sensor(rhs, conf)


BUILD_FLAGS = '-DUSE_CUSTOM_TEXT_SENSOR'
