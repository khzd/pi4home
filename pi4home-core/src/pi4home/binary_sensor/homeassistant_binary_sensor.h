#ifndef PI4HOME_HOMEASSISTANT_BINARY_SENSOR_H
#define PI4HOME_HOMEASSISTANT_BINARY_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_HOMEASSISTANT_BINARY_SENSOR

#include "pi4home/component.h"
#include "pi4home/binary_sensor/binary_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace binary_sensor {

class HomeassistantBinarySensor : public BinarySensor, public Component {
 public:
  HomeassistantBinarySensor(const std::string &name, const std::string &entity_id);
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;

 protected:
  std::string entity_id_;
};

}  // namespace binary_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_HOMEASSISTANT_BINARY_SENSOR

#endif  // PI4HOME_HOMEASSISTANT_BINARY_SENSOR_H
