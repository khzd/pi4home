import voluptuous as vol

from pi4home.components import i2c, sensor
import pi4home.config_validation as cv
from pi4home.const import CONF_HUMIDITY, CONF_ID, CONF_NAME, CONF_TEMPERATURE, \
    CONF_UPDATE_INTERVAL
from pi4home.cpp_generator import Pvariable
from pi4home.cpp_helpers import setup_component
from pi4home.cpp_types import App, Application, PollingComponent

DEPENDENCIES = ['i2c']

MakeHTU21DSensor = Application.struct('MakeHTU21DSensor')
HTU21DComponent = sensor.sensor_ns.class_('HTU21DComponent', PollingComponent, i2c.I2CDevice)
HTU21DTemperatureSensor = sensor.sensor_ns.class_('HTU21DTemperatureSensor',
                                                  sensor.EmptyPollingParentSensor)
HTU21DHumiditySensor = sensor.sensor_ns.class_('HTU21DHumiditySensor',
                                               sensor.EmptyPollingParentSensor)

PLATFORM_SCHEMA = sensor.PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(HTU21DComponent),
    vol.Required(CONF_TEMPERATURE): cv.nameable(sensor.SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_variable_id(HTU21DTemperatureSensor),
    })),
    vol.Required(CONF_HUMIDITY): cv.nameable(sensor.SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_variable_id(HTU21DHumiditySensor),
    })),
    vol.Optional(CONF_UPDATE_INTERVAL): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA.schema)


def to_code(config):
    rhs = App.make_htu21d_sensor(config[CONF_TEMPERATURE][CONF_NAME],
                                 config[CONF_HUMIDITY][CONF_NAME],
                                 config.get(CONF_UPDATE_INTERVAL))
    htu21d = Pvariable(config[CONF_ID], rhs)

    sensor.setup_sensor(htu21d.Pget_temperature_sensor(), config[CONF_TEMPERATURE])
    sensor.setup_sensor(htu21d.Pget_humidity_sensor(), config[CONF_HUMIDITY])
    setup_component(htu21d, config)


BUILD_FLAGS = '-DUSE_HTU21D_SENSOR'
