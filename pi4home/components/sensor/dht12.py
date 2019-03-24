import voluptuous as vol

from pi4home.components import i2c, sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_HUMIDITY, CONF_ID, CONF_NAME, CONF_TEMPERATURE, \
    CONF_UPDATE_INTERVAL
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, PollingComponent

DEPENDENCIES = ['i2c']

DHT12Component = sensor.sensor_ns.class_('DHT12Component', PollingComponent, i2c.I2CDevice)
DHT12TemperatureSensor = sensor.sensor_ns.class_('DHT12TemperatureSensor',
                                                 sensor.EmptyPollingParentSensor)
DHT12HumiditySensor = sensor.sensor_ns.class_('DHT12HumiditySensor',
                                              sensor.EmptyPollingParentSensor)

PLATFORM_SCHEMA = sensor.PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(DHT12Component),
    vol.Required(CONF_TEMPERATURE): cv.nameable(sensor.SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_variable_id(DHT12TemperatureSensor),
    })),
    vol.Required(CONF_HUMIDITY): cv.nameable(sensor.SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_variable_id(DHT12HumiditySensor),
    })),
    vol.Optional(CONF_UPDATE_INTERVAL): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    rhs = App.make_dht12_sensor(config[CONF_TEMPERATURE][CONF_NAME],
                                config[CONF_HUMIDITY][CONF_NAME],
                                config.get(CONF_UPDATE_INTERVAL))
    dht = Pvariable(config[CONF_ID], rhs)

    sensor.setup_sensor(dht.Pget_temperature_sensor(), config[CONF_TEMPERATURE])
    sensor.setup_sensor(dht.Pget_humidity_sensor(), config[CONF_HUMIDITY])
    setup_component(dht, config)


BUILD_FLAGS = '-DUSE_DHT12_SENSOR'
