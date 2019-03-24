import voluptuous as vol

from pi4home.components import i2c, sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ADDRESS, CONF_ID
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Component

DEPENDENCIES = ['i2c']
MULTI_CONF = True

ADS1115Component = sensor.sensor_ns.class_('ADS1115Component', Component, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_variable_id(ADS1115Component),
    vol.Required(CONF_ADDRESS): cv.i2c_address,
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    rhs = App.make_ads1115_component(config[CONF_ADDRESS])
    var = Pvariable(config[CONF_ID], rhs)
    setup_component(var, config)


BUILD_FLAGS = '-DUSE_ADS1115_SENSOR'
