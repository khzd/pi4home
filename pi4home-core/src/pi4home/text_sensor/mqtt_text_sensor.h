#ifndef PI4HOME_MQTT_TEXT_SENSOR_H
#define PI4HOME_MQTT_TEXT_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_MQTT_TEXT_SENSOR

#include "pi4home/component.h"
#include "pi4home/mqtt/mqtt_component.h"
#include "pi4home/text_sensor/text_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace text_sensor {

class MQTTTextSensor : public mqtt::MQTTComponent {
 public:
  explicit MQTTTextSensor(TextSensor *sensor);

  void send_discovery(JsonObject &root, mqtt::SendDiscoveryConfig &config) override;

  void setup() override;

  void dump_config() override;

  bool publish_state(const std::string &value);

  bool send_initial_state() override;

  bool is_internal() override;

 protected:
  std::string component_type() const override;

  std::string friendly_name() const override;

  TextSensor *sensor_;
};

}  // namespace text_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_MQTT_TEXT_SENSOR

#endif  // PI4HOME_MQTT_TEXT_SENSOR_H
