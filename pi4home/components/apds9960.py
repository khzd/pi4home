import voluptuous as vol

from pi4home.components import i2c, sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ADDRESS, CONF_ID, CONF_UPDATE_INTERVAL
from pi4home.cpp_generator import Pvariable, add
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, PollingComponent

DEPENDENCIES = ['i2c']
MULTI_CONF = True

CONF_APDS9960_ID = 'apds9960_id'
APDS9960 = sensor.sensor_ns.class_('APDS9960', PollingComponent, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_variable_id(APDS9960),
    vol.Optional(CONF_ADDRESS): cv.i2c_address,
    vol.Optional(CONF_UPDATE_INTERVAL): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    rhs = App.make_apds9960(config.get(CONF_UPDATE_INTERVAL))
    var = Pvariable(config[CONF_ID], rhs)

    if CONF_ADDRESS in config:
        add(var.set_address(config[CONF_ADDRESS]))

    setup_component(var, config)


BUILD_FLAGS = '-DUSE_APDS9960'
