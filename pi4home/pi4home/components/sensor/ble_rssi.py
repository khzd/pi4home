import voluptuous as vol

from pi4home.components import sensor
from pi4home.components.esp32_ble_tracker import CONF_ESP32_BLE_ID, ESP32BLETracker, \
    make_address_array
import pi4home.config_validation as cv
from pi4home.const import CONF_MAC_ADDRESS, CONF_NAME
from pi4home.cpp_generator import get_variable
from pi4home.cpp_types import pi4home_ns

DEPENDENCIES = ['esp32_ble_tracker']

ESP32BLERSSISensor = pi4home_ns.class_('ESP32BLERSSISensor', sensor.Sensor)

PLATFORM_SCHEMA = cv.nameable(sensor.SENSOR_PLATFORM_SCHEMA.extend({
    cv.GenerateID(): cv.declare_variable_id(ESP32BLERSSISensor),
    vol.Required(CONF_MAC_ADDRESS): cv.mac_address,
    cv.GenerateID(CONF_ESP32_BLE_ID): cv.use_variable_id(ESP32BLETracker)
}))


def to_code(config):
    for hub in get_variable(config[CONF_ESP32_BLE_ID]):
        yield
    rhs = hub.make_rssi_sensor(config[CONF_NAME], make_address_array(config[CONF_MAC_ADDRESS]))
    sensor.register_sensor(rhs, config)
