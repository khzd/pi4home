#ifndef PI4HOME_COVER_MQTT_COVER_COMPONENT_H
#define PI4HOME_COVER_MQTT_COVER_COMPONENT_H

#include "pi4home/defines.h"

#ifdef USE_MQTT_COVER

#include "pi4home/mqtt/mqtt_component.h"
#include "pi4home/cover/cover.h"

PI4HOME_NAMESPACE_BEGIN

namespace cover {

class MQTTCoverComponent : public mqtt::MQTTComponent {
 public:
  explicit MQTTCoverComponent(Cover *cover);

  void setup() override;
  void send_discovery(JsonObject &root, mqtt::SendDiscoveryConfig &config) override;

  bool send_initial_state() override;
  bool is_internal() override;

  bool publish_state(cover::CoverState state);

  void dump_config() override;

 protected:
  std::string component_type() const override;
  std::string friendly_name() const override;

  Cover *cover_;
};

}  // namespace cover

PI4HOME_NAMESPACE_END

#endif  // USE_MQTT_COVER

#endif  // PI4HOME_COVER_MQTT_COVER_COMPONENT_H
