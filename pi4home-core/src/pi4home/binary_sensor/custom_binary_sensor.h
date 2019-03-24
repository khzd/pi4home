#ifndef PI4HOME_BINARY_SENSOR_CUSTOM_BINARY_SENSOR_H
#define PI4HOME_BINARY_SENSOR_CUSTOM_BINARY_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_CUSTOM_BINARY_SENSOR

#include "pi4home/component.h"
#include "pi4home/binary_sensor/binary_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace binary_sensor {

class CustomBinarySensorConstructor : public Component {
 public:
  CustomBinarySensorConstructor(const std::function<std::vector<BinarySensor *>()> &init);

  BinarySensor *get_binary_sensor(int i);

  void dump_config() override;

 protected:
  std::vector<BinarySensor *> binary_sensors_;
};

}  // namespace binary_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_CUSTOM_BINARY_SENSOR

#endif  // PI4HOME_BINARY_SENSOR_CUSTOM_BINARY_SENSOR_H
