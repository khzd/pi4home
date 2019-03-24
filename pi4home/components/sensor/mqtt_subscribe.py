import voluptuous as vol

from pi4home.components import sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_NAME, CONF_QOS, CONF_TOPIC
from pi4home.cpp_generator import Pvariable, add
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Component

DEPENDENCIES = ['mqtt']

MQTTSubscribeSensor = sensor.sensor_ns.class_('MQTTSubscribeSensor', sensor.Sensor, Component)

PLATFORM_SCHEMA = cv.nameable(sensor.SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(MQTTSubscribeSensor),
    vol.Required(CONF_TOPIC): cv.subscribe_topic,
    vol.Optional(CONF_QOS): cv.mqtt_qos,
}).extend(cv.COMPONENT_SCHEMA.schema))


def to_code(config):
    rhs = App.make_mqtt_subscribe_sensor(config[CONF_NAME], config[CONF_TOPIC])
    subs = Pvariable(config[CONF_ID], rhs)

    if CONF_QOS in config:
        add(subs.set_qos(config[CONF_QOS]))

    sensor.setup_sensor(subs, config)
    setup_component(subs, config)


BUILD_FLAGS = '-DUSE_MQTT_SUBSCRIBE_SENSOR'
