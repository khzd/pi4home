import voluptuous as vol

from pi4home import automation
from pi4home.components import mqtt
from pi4home.components.mqtt import setup_mqtt_component
import pi4home.config_validation as cv
from pi4home.const import CONF_ICON, CONF_ID, CONF_INTERNAL, CONF_MQTT_ID, CONF_ON_VALUE, \
    CONF_TRIGGER_ID
from pi4home.core import CORE
from pi4home.cpp_generator import Pvariable, add
from pi4home.cpp_types import App, Nameable, Trigger, pi4home_ns, std_string, Action

PLATFORM_SCHEMA = cv.PLATFORM_SCHEMA.extend({

})

# pylint: disable=invalid-name
text_sensor_ns = pi4home_ns.namespace('text_sensor')
TextSensor = text_sensor_ns.class_('TextSensor', Nameable)
TextSensorPtr = TextSensor.operator('ptr')
MQTTTextSensor = text_sensor_ns.class_('MQTTTextSensor', mqtt.MQTTComponent)

TextSensorStateTrigger = text_sensor_ns.class_('TextSensorStateTrigger',
                                               Trigger.template(std_string))
TextSensorPublishAction = text_sensor_ns.class_('TextSensorPublishAction', Action)

TEXT_SENSOR_SCHEMA = cv.MQTT_COMPONENT_SCHEMA.extend({
    cv.GenerateID(CONF_MQTT_ID): cv.declare_variable_id(MQTTTextSensor),
    vol.Optional(CONF_ICON): cv.icon,
    vol.Optional(CONF_ON_VALUE): automation.validate_automation({
        cv.GenerateID(CONF_TRIGGER_ID): cv.declare_variable_id(TextSensorStateTrigger),
    }),
})

TEXT_SENSOR_PLATFORM_SCHEMA = PLATFORM_SCHEMA.extend(TEXT_SENSOR_SCHEMA.schema)


def setup_text_sensor_core_(text_sensor_var, config):
    if CONF_INTERNAL in config:
        add(text_sensor_var.set_internal(config[CONF_INTERNAL]))
    if CONF_ICON in config:
        add(text_sensor_var.set_icon(config[CONF_ICON]))

    for conf in config.get(CONF_ON_VALUE, []):
        rhs = text_sensor_var.make_state_trigger()
        trigger = Pvariable(conf[CONF_TRIGGER_ID], rhs)
        automation.build_automations(trigger, [(std_string, 'x')], conf)

    setup_mqtt_component(text_sensor_var.get_mqtt(), config)


def setup_text_sensor(text_sensor_obj, config):
    if not CORE.has_id(config[CONF_ID]):
        text_sensor_obj = Pvariable(config[CONF_ID], text_sensor_obj, has_side_effects=True)
    CORE.add_job(setup_text_sensor_core_, text_sensor_obj, config)


def register_text_sensor(var, config):
    if not CORE.has_id(config[CONF_ID]):
        var = Pvariable(config[CONF_ID], var, has_side_effects=True)
    add(App.register_text_sensor(var))
    CORE.add_job(setup_text_sensor_core_, var, config)


BUILD_FLAGS = '-DUSE_TEXT_SENSOR'
