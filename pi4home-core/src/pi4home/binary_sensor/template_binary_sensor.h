#ifndef PI4HOME_BINARY_SENSOR_TEMPLATE_BINARY_SENSOR_H
#define PI4HOME_BINARY_SENSOR_TEMPLATE_BINARY_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_TEMPLATE_BINARY_SENSOR

#include "pi4home/component.h"
#include "pi4home/binary_sensor/binary_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace binary_sensor {

class TemplateBinarySensor : public Component, public BinarySensor {
 public:
  explicit TemplateBinarySensor(const std::string &name);

  void set_template(std::function<optional<bool>()> &&f);

  void loop() override;
  void dump_config() override;

  float get_setup_priority() const override;

 protected:
  optional<std::function<optional<bool>()>> f_;
};

}  // namespace binary_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_TEMPLATE_BINARY_SENSOR

#endif  // PI4HOME_BINARY_SENSOR_TEMPLATE_BINARY_SENSOR_H
