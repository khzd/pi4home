#include "pi4home/defines.h"

#ifdef USE_CUSTOM_TEXT_SENSOR

#include "pi4home/text_sensor/custom_text_sensor.h"
#include "pi4home/log.h"

PI4HOME_NAMESPACE_BEGIN

namespace text_sensor {

static const char *TAG = "text_sensor.custom";

CustomTextSensorConstructor::CustomTextSensorConstructor(std::function<std::vector<TextSensor *>()> init) {
  this->text_sensors_ = init();
}
TextSensor *CustomTextSensorConstructor::get_text_sensor(int i) { return this->text_sensors_[i]; }
void CustomTextSensorConstructor::dump_config() {
  for (auto *child : this->text_sensors_) {
    LOG_TEXT_SENSOR("", "Custom Text Sensor", child);
  }
}

}  // namespace text_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_CUSTOM_TEXT_SENSOR
