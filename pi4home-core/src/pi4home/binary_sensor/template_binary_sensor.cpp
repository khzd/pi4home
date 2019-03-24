#include "pi4home/defines.h"

#ifdef USE_TEMPLATE_BINARY_SENSOR

#include "pi4home/binary_sensor/template_binary_sensor.h"
#include "pi4home/log.h"

PI4HOME_NAMESPACE_BEGIN

namespace binary_sensor {

static const char *TAG = "binary_sensor.template";

TemplateBinarySensor::TemplateBinarySensor(const std::string &name) : BinarySensor(name) {}
void TemplateBinarySensor::loop() {
  if (!this->f_.has_value())
    return;

  auto s = (*this->f_)();
  if (s.has_value()) {
    this->publish_state(*s);
  }
}
float TemplateBinarySensor::get_setup_priority() const { return setup_priority::HARDWARE; }
void TemplateBinarySensor::set_template(std::function<optional<bool>()> &&f) { this->f_ = f; }
void TemplateBinarySensor::dump_config() { LOG_BINARY_SENSOR("", "Template Binary Sensor", this); }

}  // namespace binary_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_TEMPLATE_BINARY_SENSOR
