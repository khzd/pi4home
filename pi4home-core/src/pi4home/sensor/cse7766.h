#ifndef PI4HOME_SENSOR_CSE7766_H
#define PI4HOME_SENSOR_CSE7766_H

#include "pi4home/defines.h"

#ifdef USE_CSE7766

#include "pi4home/component.h"
#include "pi4home/uart_component.h"
#include "pi4home/helpers.h"
#include "pi4home/sensor/sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

using CSE7766VoltageSensor = EmptySensor<1, ICON_FLASH, UNIT_V>;
using CSE7766CurrentSensor = EmptySensor<1, ICON_FLASH, UNIT_A>;
using CSE7766PowerSensor = EmptySensor<1, ICON_FLASH, UNIT_W>;

class CSE7766Component : public PollingComponent, public UARTDevice {
 public:
  CSE7766Component(UARTComponent *parent, uint32_t update_interval = 60000);

  CSE7766VoltageSensor *make_voltage_sensor(const std::string &name);

  CSE7766CurrentSensor *make_current_sensor(const std::string &name);

  CSE7766PowerSensor *make_power_sensor(const std::string &name);

  void loop() override;
  float get_setup_priority() const override;
  void update() override;
  void setup() override;
  void dump_config() override;

 protected:
  bool check_byte_();
  void parse_data_();
  uint32_t get_24_bit_uint_(uint8_t start_index);

  uint8_t raw_data_[24];
  uint8_t raw_data_index_{0};
  uint32_t last_transmission_{0};
  CSE7766VoltageSensor *voltage_{nullptr};
  CSE7766CurrentSensor *current_{nullptr};
  CSE7766PowerSensor *power_{nullptr};
  float voltage_acc_{0.0};
  float current_acc_{0.0};
  float power_acc_{0.0};
  uint32_t last_reading_{0};
  uint32_t last_update_{0};
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_CSE7766

#endif  // PI4HOME_SENSOR_CSE7766_H
