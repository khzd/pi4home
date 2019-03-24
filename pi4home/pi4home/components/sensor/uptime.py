import voluptuous as vol

from pi4home.components import sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_NAME, CONF_UPDATE_INTERVAL
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App

UptimeSensor = sensor.sensor_ns.class_('UptimeSensor', sensor.PollingSensorComponent)

PLATFORM_SCHEMA = cv.nameable(sensor.SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(UptimeSensor),
    vol.Optional(CONF_UPDATE_INTERVAL): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA.schema))


def to_code(config):
    rhs = App.make_uptime_sensor(config[CONF_NAME], config.get(CONF_UPDATE_INTERVAL))
    uptime = Pvariable(config[CONF_ID], rhs)

    sensor.setup_sensor(uptime, config)
    setup_component(uptime, config)


BUILD_FLAGS = '-DUSE_UPTIME_SENSOR'
