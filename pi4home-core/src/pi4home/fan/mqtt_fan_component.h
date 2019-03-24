#ifndef PI4HOME_FAN_MQTT_FAN_COMPONENT_H
#define PI4HOME_FAN_MQTT_FAN_COMPONENT_H

#include "pi4home/defines.h"

#ifdef USE_MQTT_FAN

#include "pi4home/mqtt/mqtt_component.h"
#include "pi4home/fan/fan_state.h"

PI4HOME_NAMESPACE_BEGIN

namespace fan {

class MQTTFanComponent : public mqtt::MQTTComponent {
 public:
  explicit MQTTFanComponent(FanState *state);

  /// Set a custom oscillation command topic. Defaults to "<base>/oscillation/command".
  void set_custom_oscillation_command_topic(const std::string &topic);
  /// Set a custom oscillation state topic. Defaults to "<base>/oscillation/state".
  void set_custom_oscillation_state_topic(const std::string &topic);
  /// Set a custom speed command topic. Defaults to "<base>/speed/command".
  void set_custom_speed_command_topic(const std::string &topic);
  /// Set a custom speed state topic. Defaults to "<base>/speed/state".
  void set_custom_speed_state_topic(const std::string &topic);

  void send_discovery(JsonObject &root, mqtt::SendDiscoveryConfig &config) override;

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  /// Setup the fan subscriptions and discovery.
  void setup() override;
  /// Send the full current state to MQTT.
  bool send_initial_state() override;
  bool publish_state();
  /// 'fan' component type for discovery.
  std::string component_type() const override;

  const std::string get_oscillation_command_topic() const;
  const std::string get_oscillation_state_topic() const;
  const std::string get_speed_command_topic() const;
  const std::string get_speed_state_topic() const;

  FanState *get_state() const;

  bool is_internal() override;

 protected:
  std::string friendly_name() const override;

  std::string custom_oscillation_command_topic_;
  std::string custom_oscillation_state_topic_;
  std::string custom_speed_command_topic_;
  std::string custom_speed_state_topic_;
  FanState *state_;
};

}  // namespace fan

PI4HOME_NAMESPACE_END

#endif  // USE_MQTT_FAN

#endif  // PI4HOME_FAN_MQTT_FAN_COMPONENT_H
