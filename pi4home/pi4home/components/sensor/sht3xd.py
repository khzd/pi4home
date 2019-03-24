import voluptuous as vol

from pi4home.components import i2c, sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_ADDRESS, CONF_HUMIDITY, CONF_ID, CONF_NAME, \
    CONF_TEMPERATURE, CONF_UPDATE_INTERVAL
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, PollingComponent

DEPENDENCIES = ['i2c']

SHT3XDComponent = sensor.sensor_ns.class_('SHT3XDComponent', PollingComponent, i2c.I2CDevice)
SHT3XDTemperatureSensor = sensor.sensor_ns.class_('SHT3XDTemperatureSensor',
                                                  sensor.EmptyPollingParentSensor)
SHT3XDHumiditySensor = sensor.sensor_ns.class_('SHT3XDHumiditySensor',
                                               sensor.EmptyPollingParentSensor)

PLATFORM_SCHEMA = sensor.PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(SHT3XDComponent),
    vol.Required(CONF_TEMPERATURE): cv.nameable(sensor.SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_variable_id(SHT3XDTemperatureSensor),
    })),
    vol.Required(CONF_HUMIDITY): cv.nameable(sensor.SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_variable_id(SHT3XDHumiditySensor),
    })),
    vol.Optional(CONF_ADDRESS, default=0x44): cv.i2c_address,
    vol.Optional(CONF_UPDATE_INTERVAL): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    rhs = App.make_sht3xd_sensor(config[CONF_TEMPERATURE][CONF_NAME],
                                 config[CONF_HUMIDITY][CONF_NAME],
                                 config[CONF_ADDRESS],
                                 config.get(CONF_UPDATE_INTERVAL))
    sht3xd = Pvariable(config[CONF_ID], rhs)

    sensor.setup_sensor(sht3xd.Pget_temperature_sensor(), config[CONF_TEMPERATURE])
    sensor.setup_sensor(sht3xd.Pget_humidity_sensor(), config[CONF_HUMIDITY])
    setup_component(sht3xd, config)


BUILD_FLAGS = '-DUSE_SHT3XD'
