#ifndef PI4HOME_SENSOR_DHT12_COMPONENT_H
#define PI4HOME_SENSOR_DHT12_COMPONENT_H

#include "pi4home/defines.h"

#ifdef USE_DHT12_SENSOR

#include "pi4home/sensor/sensor.h"
#include "pi4home/i2c_component.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

using DHT12TemperatureSensor = EmptyPollingParentSensor<1, ICON_EMPTY, UNIT_C>;
using DHT12HumiditySensor = EmptyPollingParentSensor<0, ICON_WATER_PERCENT, UNIT_PERCENT>;

class DHT12Component : public PollingComponent, public I2CDevice {
 public:
  DHT12Component(I2CComponent *parent, const std::string &temperature_name, const std::string &humidity_name,
                 uint32_t update_interval = 60000);

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;
  DHT12TemperatureSensor *get_temperature_sensor() const;
  DHT12HumiditySensor *get_humidity_sensor() const;

 protected:
  bool read_data_(uint8_t *data);

  DHT12TemperatureSensor *temperature_sensor_;
  DHT12HumiditySensor *humidity_sensor_;
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_DHT12_SENSOR

#endif  // PI4HOME_SENSOR_DHT12_COMPONENT_H
