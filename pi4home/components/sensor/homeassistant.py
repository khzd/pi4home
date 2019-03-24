import voluptuous as vol

from pi4home.components import sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ENTITY_ID, CONF_ID, CONF_NAME
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_types import App

DEPENDENCIES = ['api']

HomeassistantSensor = sensor.sensor_ns.class_('HomeassistantSensor', sensor.Sensor)

PLATFORM_SCHEMA = cv.nameable(sensor.SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(HomeassistantSensor),
    vol.Required(CONF_ENTITY_ID): cv.entity_id,
}))


def to_code(config):
    rhs = App.make_homeassistant_sensor(config[CONF_NAME], config[CONF_ENTITY_ID])
    subs = Pvariable(config[CONF_ID], rhs)
    sensor.setup_sensor(subs, config)


BUILD_FLAGS = '-DUSE_HOMEASSISTANT_SENSOR'
