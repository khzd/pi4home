#ifndef PI4HOME_MHZ_19_COMPONENT_H
#define PI4HOME_MHZ_19_COMPONENT_H

#include "pi4home/defines.h"

#ifdef USE_MHZ19

#include "pi4home/component.h"
#include "pi4home/uart_component.h"
#include "pi4home/sensor/sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

using MHZ19TemperatureSensor = sensor::EmptyPollingParentSensor<0, ICON_EMPTY, UNIT_C>;
using MHZ19CO2Sensor = sensor::EmptyPollingParentSensor<0, ICON_PERIODIC_TABLE_CO2, UNIT_PPM>;

class MHZ19Component : public PollingComponent, public UARTDevice {
 public:
  MHZ19Component(UARTComponent *parent, const std::string &name, uint32_t update_interval = 60000);

  float get_setup_priority() const override;

  void update() override;
  void dump_config() override;

  MHZ19TemperatureSensor *make_temperature_sensor(const std::string &name);
  MHZ19CO2Sensor *get_co2_sensor() const;

 protected:
  bool mhz19_write_command_(const uint8_t *command, uint8_t *response);

  MHZ19TemperatureSensor *temperature_sensor_{nullptr};
  MHZ19CO2Sensor *co2_sensor_;
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_MHZ19

#endif  // PI4HOME_MHZ_19_COMPONENT_H
