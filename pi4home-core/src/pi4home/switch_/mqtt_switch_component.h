#ifndef PI4HOME_SWITCH_MQTT_SWITCH_COMPONENT_H
#define PI4HOME_SWITCH_MQTT_SWITCH_COMPONENT_H

#include "pi4home/defines.h"

#ifdef USE_MQTT_SWITCH

#include "pi4home/binary_sensor/mqtt_binary_sensor_component.h"
#include "pi4home/mqtt/mqtt_component.h"
#include "pi4home/switch_/switch.h"

PI4HOME_NAMESPACE_BEGIN

namespace switch_ {

/** MQTT representation of switches
 *
 * Overrides MQTTBinarySensorComponent with a callback that can write values to hardware.
 */
class MQTTSwitchComponent : public mqtt::MQTTComponent {
 public:
  explicit MQTTSwitchComponent(switch_::Switch *a_switch);

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  void setup() override;
  void dump_config() override;

  void send_discovery(JsonObject &root, mqtt::SendDiscoveryConfig &config) override;

  bool send_initial_state() override;
  bool is_internal() override;

  bool publish_state(bool state);

 protected:
  std::string friendly_name() const override;

  /// "switch" component type.
  std::string component_type() const override;

  Switch *switch_;
};

}  // namespace switch_

PI4HOME_NAMESPACE_END

#endif  // USE_MQTT_SWITCH

#endif  // PI4HOME_SWITCH_MQTT_SWITCH_COMPONENT_H
