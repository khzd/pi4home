#ifndef PI4HOME_MQTT_SUBSCRIBE_TEXT_SENSOR_H
#define PI4HOME_MQTT_SUBSCRIBE_TEXT_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_MQTT_SUBSCRIBE_TEXT_SENSOR

#include "pi4home/component.h"
#include "pi4home/text_sensor/text_sensor.h"
#include "pi4home/mqtt/mqtt_client_component.h"

PI4HOME_NAMESPACE_BEGIN

namespace text_sensor {

class MQTTSubscribeTextSensor : public TextSensor, public Component {
 public:
  MQTTSubscribeTextSensor(const std::string &name, std::string topic);

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void set_qos(uint8_t qos);

 protected:
  std::string topic_;
  uint8_t qos_{0};
};

}  // namespace text_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_MQTT_SUBSCRIBE_TEXT_SENSOR

#endif  // PI4HOME_MQTT_SUBSCRIBE_TEXT_SENSOR_H
