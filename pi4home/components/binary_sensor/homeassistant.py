import voluptuous as vol

from pi4home.components import binary_sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ENTITY_ID, CONF_ID, CONF_NAME
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_types import App

DEPENDENCIES = ['api']

HomeassistantBinarySensor = binary_sensor.binary_sensor_ns.class_('HomeassistantBinarySensor',
                                                                  binary_sensor.BinarySensor)

PLATFORM_SCHEMA = cv.nameable(binary_sensor.BINARY_SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(HomeassistantBinarySensor),
    vol.Required(CONF_ENTITY_ID): cv.entity_id,
}))


def to_code(config):
    rhs = App.make_homeassistant_binary_sensor(config[CONF_NAME], config[CONF_ENTITY_ID])
    subs = Pvariable(config[CONF_ID], rhs)
    binary_sensor.setup_binary_sensor(subs, config)


BUILD_FLAGS = '-DUSE_HOMEASSISTANT_BINARY_SENSOR'
