#ifndef PI4HOME_SENSOR_CUSTOM_SENSOR_H
#define PI4HOME_SENSOR_CUSTOM_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_CUSTOM_SENSOR

#include "pi4home/component.h"
#include "pi4home/sensor/sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

class CustomSensorConstructor : public Component {
 public:
  CustomSensorConstructor(const std::function<std::vector<Sensor *>()> &init);

  Sensor *get_sensor(int i);

  void dump_config() override;

 protected:
  std::vector<Sensor *> sensors_;
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_CUSTOM_SENSOR

#endif  // PI4HOME_SENSOR_CUSTOM_SENSOR_H
