// Based on:
//   - https://cdn-shop.adafruit.com/datasheets/TSL2561.pdf
//   - https://github.com/adafruit/TSL2561-Arduino-Library

#include "pi4home/defines.h"

#ifdef USE_TSL2561

#include "pi4home/sensor/tsl2561_sensor.h"
#include "pi4home/log.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

static const char *TAG = "sensor.tsl2561";

static const uint8_t TSL2561_COMMAND_BIT = 0x80;
static const uint8_t TSL2561_WORD_BIT = 0x20;
static const uint8_t TSL2561_REGISTER_CONTROL = 0x00;
static const uint8_t TSL2561_REGISTER_TIMING = 0x01;
static const uint8_t TSL2561_REGISTER_ID = 0x0A;
static const uint8_t TSL2561_REGISTER_DATA_0 = 0x0C;
static const uint8_t TSL2561_REGISTER_DATA_1 = 0x0E;

TSL2561Sensor::TSL2561Sensor(I2CComponent *parent, const std::string &name, uint8_t address, uint32_t update_interval)
    : PollingSensorComponent(name, update_interval), I2CDevice(parent, address) {}

void TSL2561Sensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up TSL2561...");
  uint8_t id;
  if (!this->tsl2561_read_byte(TSL2561_REGISTER_ID, &id)) {
    this->mark_failed();
    return;
  }

  uint8_t timing;
  if (!this->tsl2561_read_byte(TSL2561_REGISTER_TIMING, &timing)) {
    this->mark_failed();
    return;
  }

  timing &= ~0b00010000;
  timing |= this->gain_ == TSL2561_GAIN_16X ? 0b00010000 : 0;

  timing &= ~0b00000011;
  timing |= this->integration_time_ & 0b11;

  this->tsl2561_write_byte(TSL2561_REGISTER_TIMING, timing);
}
void TSL2561Sensor::dump_config() {
  LOG_SENSOR("", "TSL2561", this);
  LOG_I2C_DEVICE(this);

  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with TSL2561 failed!");
  }

  int gain = this->gain_ == TSL2561_GAIN_1X ? 1 : 16;
  ESP_LOGCONFIG(TAG, "  Gain: %dx", gain);
  ESP_LOGCONFIG(TAG, "  Integration Time: %.1f ms", this->get_integration_time_ms_());

  LOG_UPDATE_INTERVAL(this);
}
void TSL2561Sensor::update() {
  // Power on
  if (!this->tsl2561_write_byte(TSL2561_REGISTER_CONTROL, 0b00000011)) {
    this->status_set_warning();
    return;
  }

  // Make sure the data is there when we will read it.
  auto timeout = static_cast<uint32_t>(this->get_integration_time_ms_() + 20);

  this->set_timeout("illuminance", timeout, [this]() { this->read_data_(); });
}

float TSL2561Sensor::calculate_lx_(uint16_t ch0, uint16_t ch1) {
  if ((ch0 == 0xFFFF) || (ch1 == 0xFFFF)) {
    ESP_LOGW(TAG, "TSL2561 sensor is saturated.");
    return NAN;
  }

  float d0 = ch0, d1 = ch1;
  float ratio = d1 / d0;

  float ms = this->get_integration_time_ms_();
  d0 *= (402.0f / ms);
  d1 *= (402.0f / ms);

  if (this->gain_ == TSL2561_GAIN_1X) {
    d0 *= 16;
    d1 *= 16;
  }

  if (this->package_cs_) {
    if (ratio < 0.52f) {
      return 0.0315f * d0 - 0.0593f * d0 * powf(ratio, 1.4f);
    } else if (ratio < 0.65f) {
      return 0.0229f * d0 - 0.0291f * d1;
    } else if (ratio < 0.80f) {
      return 0.0157f * d0 - 0.0153f * d1;
    } else if (ratio < 1.30f) {
      return 0.00338f * d0 - 0.00260f * d1;
    }

    return 0.0f;
  } else {
    if (ratio < 0.5f) {
      return 0.0304f * d0 - 0.062f * d0 * powf(ratio, 1.4f);
    } else if (ratio < 0.61f) {
      return 0.0224f * d0 - 0.031f * d1;
    } else if (ratio < 0.80f) {
      return 0.0128f * d0 - 0.0153f * d1;
    } else if (ratio < 1.30f) {
      return 0.00146f * d0 - 0.00112f * d1;
    }
    return 0.0f;
  }
}
void TSL2561Sensor::read_data_() {
  uint16_t data1, data0;
  if (!this->tsl2561_read_uint(TSL2561_WORD_BIT | TSL2561_REGISTER_DATA_1, &data1)) {
    this->status_set_warning();
    return;
  }
  if (!this->tsl2561_read_uint(TSL2561_WORD_BIT | TSL2561_REGISTER_DATA_0, &data0)) {
    this->status_set_warning();
    return;
  }
  // Power off
  if (!this->tsl2561_write_byte(TSL2561_REGISTER_CONTROL, 0b00000000)) {
    this->status_set_warning();
    return;
  }

  float lx = this->calculate_lx_(data0, data1);
  ESP_LOGD(TAG, "Got illuminance=%.1flx", lx);
  this->publish_state(lx);
  this->status_clear_warning();
}
std::string TSL2561Sensor::unit_of_measurement() { return UNIT_LX; }
std::string TSL2561Sensor::icon() { return ICON_BRIGHTNESS_5; }
int8_t TSL2561Sensor::accuracy_decimals() { return 1; }
float TSL2561Sensor::get_integration_time_ms_() {
  switch (this->integration_time_) {
    case TSL2561_INTEGRATION_14MS:
      return 13.7f;
    case TSL2561_INTEGRATION_101MS:
      return 100.0f;
    case TSL2561_INTEGRATION_402MS:
      return 402.0f;
  }
  return 0.0f;
}
void TSL2561Sensor::set_integration_time(TSL2561IntegrationTime integration_time) {
  this->integration_time_ = integration_time;
}
void TSL2561Sensor::set_gain(TSL2561Gain gain) { this->gain_ = gain; }
void TSL2561Sensor::set_is_cs_package(bool package_cs) { this->package_cs_ = package_cs; }
float TSL2561Sensor::get_setup_priority() const { return setup_priority::HARDWARE_LATE; }
bool TSL2561Sensor::tsl2561_write_byte(uint8_t a_register, uint8_t value) {
  return this->write_byte(a_register | TSL2561_COMMAND_BIT, value);
}
bool TSL2561Sensor::tsl2561_read_uint(uint8_t a_register, uint16_t *value) {
  uint8_t data[2];
  if (!this->read_bytes(a_register | TSL2561_COMMAND_BIT, data, 2))
    return false;
  const uint16_t hi = data[1];
  const uint16_t lo = data[0];
  *value = (hi << 8) | lo;
  return true;
}
bool TSL2561Sensor::tsl2561_read_byte(uint8_t a_register, uint8_t *value) {
  return this->read_byte(a_register | TSL2561_COMMAND_BIT, value);
}

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_TSL2561