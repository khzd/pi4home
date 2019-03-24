#ifndef PI4HOME_SENSOR_MQTT_SUBSCRIBE_SENSOR_H
#define PI4HOME_SENSOR_MQTT_SUBSCRIBE_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_MQTT_SUBSCRIBE_SENSOR

#include "pi4home/component.h"
#include "pi4home/sensor/sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

class MQTTSubscribeSensor : public Sensor, public Component {
 public:
  MQTTSubscribeSensor(const std::string &name, std::string topic);

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;

  void set_qos(uint8_t qos);

 protected:
  std::string topic_;
  uint8_t qos_{0};
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_MQTT_SUBSCRIBE_SENSOR

#endif  // PI4HOME_SENSOR_MQTT_SUBSCRIBE_SENSOR_H
