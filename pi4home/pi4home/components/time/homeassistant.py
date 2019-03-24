from pi4home.components import time as time_
import pi4home.config_validation as cv
from pi4home.const import CONF_ID
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App

DEPENDENCIES = ['api']

HomeAssistantTime = time_.time_ns.class_('HomeAssistantTime', time_.RealTimeClockComponent)

PLATFORM_SCHEMA = time_.TIME_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(HomeAssistantTime),
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    rhs = App.make_homeassistant_time_component()
    ha_time = Pvariable(config[CONF_ID], rhs)
    time_.setup_time(ha_time, config)
    setup_component(ha_time, config)


BUILD_FLAGS = '-DUSE_HOMEASSISTANT_TIME'
