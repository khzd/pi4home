import voluptuous as vol

from pi4home.components import text_sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_NAME, CONF_QOS, CONF_TOPIC
from pi4home.cpp_generator import Pvariable, add
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Component

DEPENDENCIES = ['mqtt']

MQTTSubscribeTextSensor = text_sensor.text_sensor_ns.class_('MQTTSubscribeTextSensor',
                                                            text_sensor.TextSensor, Component)

PLATFORM_SCHEMA = cv.nameable(text_sensor.TEXT_SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(MQTTSubscribeTextSensor),
    vol.Required(CONF_TOPIC): cv.subscribe_topic,
    vol.Optional(CONF_QOS): cv.mqtt_qos,
}).extend(cv.COMPONENT_SCHEMA.schema))


def to_code(config):
    rhs = App.make_mqtt_subscribe_text_sensor(config[CONF_NAME], config[CONF_TOPIC])
    sensor_ = Pvariable(config[CONF_ID], rhs)

    if CONF_QOS in config:
        add(sensor_.set_qos(config[CONF_QOS]))

    text_sensor.setup_text_sensor(sensor_, config)
    setup_component(sensor_, config)


BUILD_FLAGS = '-DUSE_MQTT_SUBSCRIBE_TEXT_SENSOR'
