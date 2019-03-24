import voluptuous as vol

from pi4home import pins
from pi4home.components import sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_PIN, CONF_UPDATE_INTERVAL
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, PollingComponent

DallasComponent = sensor.sensor_ns.class_('DallasComponent', PollingComponent)
MULTI_CONF = True

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_variable_id(DallasComponent),
    vol.Required(CONF_PIN): pins.input_pin,
    vol.Optional(CONF_UPDATE_INTERVAL): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    rhs = App.make_dallas_component(config[CONF_PIN], config.get(CONF_UPDATE_INTERVAL))
    var = Pvariable(config[CONF_ID], rhs)
    setup_component(var, config)


BUILD_FLAGS = '-DUSE_DALLAS_SENSOR'
