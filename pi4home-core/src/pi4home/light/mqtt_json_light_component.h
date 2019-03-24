#ifndef PI4HOME_LIGHT_MQTT_JSON_LIGHT_COMPONENT
#define PI4HOME_LIGHT_MQTT_JSON_LIGHT_COMPONENT

#include "pi4home/defines.h"

#ifdef USE_MQTT_LIGHT

#include "pi4home/mqtt/mqtt_component.h"
#include "pi4home/light/light_state.h"

PI4HOME_NAMESPACE_BEGIN

namespace light {

class MQTTJSONLightComponent : public mqtt::MQTTComponent {
 public:
  explicit MQTTJSONLightComponent(LightState *state);

  LightState *get_state() const;

  void setup() override;

  void dump_config() override;

  void send_discovery(JsonObject &root, mqtt::SendDiscoveryConfig &config) override;

  bool send_initial_state() override;

  bool is_internal() override;

 protected:
  std::string friendly_name() const override;
  std::string component_type() const override;

  bool publish_state_();

  LightState *state_;
};

}  // namespace light

PI4HOME_NAMESPACE_END

#endif  // USE_MQTT_LIGHT

#endif  // PI4HOME_LIGHT_MQTT_JSON_LIGHT_COMPONENT
