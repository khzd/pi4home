#ifndef PI4HOME_SENSOR_ESP32_HALL_SENSOR_H
#define PI4HOME_SENSOR_ESP32_HALL_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_ESP32_HALL_SENSOR

#include "pi4home/sensor/sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

class ESP32HallSensor : public PollingSensorComponent {
 public:
  explicit ESP32HallSensor(const std::string &name, uint32_t update_interval = 60000);

  void dump_config() override;

  void update() override;

  std::string unit_of_measurement() override;
  std::string icon() override;
  int8_t accuracy_decimals() override;
  std::string unique_id() override;
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_ESP32_HALL_SENSOR

#endif  // PI4HOME_SENSOR_ESP32_HALL_SENSOR_H
