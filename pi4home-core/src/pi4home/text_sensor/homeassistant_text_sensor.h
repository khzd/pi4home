#ifndef PI4HOME_HOMEASSISTANT_TEXT_SENSOR_H
#define PI4HOME_HOMEASSISTANT_TEXT_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_HOMEASSISTANT_TEXT_SENSOR

#include "pi4home/component.h"
#include "pi4home/text_sensor/text_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace text_sensor {

class HomeassistantTextSensor : public TextSensor, public Component {
 public:
  HomeassistantTextSensor(const std::string &name, const std::string &entity_id);
  void dump_config() override;
  void setup() override;

 protected:
  std::string entity_id_;
};

}  // namespace text_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_HOMEASSISTANT_TEXT_SENSOR

#endif  // PI4HOME_HOMEASSISTANT_TEXT_SENSOR_H
