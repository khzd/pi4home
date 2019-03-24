import voluptuous as vol

from pi4home.components import sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ID, CONF_NAME, CONF_UPDATE_INTERVAL, ESP_PLATFORM_ESP32
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Application

ESP_PLATFORMS = [ESP_PLATFORM_ESP32]

MakeESP32HallSensor = Application.struct('MakeESP32HallSensor')
ESP32HallSensor = sensor.sensor_ns.class_('ESP32HallSensor', sensor.PollingSensorComponent)

PLATFORM_SCHEMA = cv.nameable(sensor.SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(ESP32HallSensor),
    vol.Optional(CONF_UPDATE_INTERVAL): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA.schema))


def to_code(config):
    rhs = App.make_esp32_hall_sensor(config[CONF_NAME], config.get(CONF_UPDATE_INTERVAL))
    hall = Pvariable(config[CONF_ID], rhs)
    sensor.setup_sensor(hall, config)
    setup_component(hall, config)


BUILD_FLAGS = '-DUSE_ESP32_HALL_SENSOR'
