#include "pi4home/defines.h"

#ifdef USE_CUSTOM_BINARY_SENSOR

#include "pi4home/binary_sensor/custom_binary_sensor.h"
#include "pi4home/log.h"

PI4HOME_NAMESPACE_BEGIN

namespace binary_sensor {

static const char *TAG = "binary_sensor.custom";

CustomBinarySensorConstructor::CustomBinarySensorConstructor(const std::function<std::vector<BinarySensor *>()> &init) {
  this->binary_sensors_ = init();
}
BinarySensor *CustomBinarySensorConstructor::get_binary_sensor(int i) { return this->binary_sensors_[i]; }
void CustomBinarySensorConstructor::dump_config() {
  for (auto *child : this->binary_sensors_) {
    LOG_BINARY_SENSOR("", "Custom Binary Sensor", child);
  }
}

}  // namespace binary_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_CUSTOM_BINARY_SENSOR
