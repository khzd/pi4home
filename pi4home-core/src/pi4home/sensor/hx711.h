#ifndef PI4HOME_SENSOR_HX711_H
#define PI4HOME_SENSOR_HX711_H

#include "pi4home/defines.h"

#ifdef USE_HX711

#include "pi4home/sensor/sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

enum HX711Gain {
  HX711_GAIN_128 = 1,
  HX711_GAIN_32 = 2,
  HX711_GAIN_64 = 3,
};

class HX711Sensor : public PollingSensorComponent {
 public:
  HX711Sensor(const std::string &name, GPIOPin *dout, GPIOPin *sck, uint32_t update_interval = 60000);

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

  void set_gain(HX711Gain gain);

  std::string unit_of_measurement() override;
  std::string icon() override;
  int8_t accuracy_decimals() override;

 protected:
  bool read_sensor_(uint32_t *result);

  GPIOPin *dout_pin_;
  GPIOPin *sck_pin_;
  HX711Gain gain_{HX711_GAIN_128};
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_HX711

#endif  // PI4HOME_SENSOR_HX711_H
