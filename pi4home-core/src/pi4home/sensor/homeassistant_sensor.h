#ifndef PI4HOME_HOMEASSISTANT_SENSOR_H
#define PI4HOME_HOMEASSISTANT_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_HOMEASSISTANT_SENSOR

#include "pi4home/component.h"
#include "pi4home/sensor/sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

class HomeassistantSensor : public Sensor, public Component {
 public:
  HomeassistantSensor(const std::string &name, const std::string &entity_id);
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;

 protected:
  std::string entity_id_;
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_HOMEASSISTANT_SENSOR

#endif  // PI4HOME_HOMEASSISTANT_SENSOR_H
