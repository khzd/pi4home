#ifndef PI4HOME_VERSION_TEXT_SENSOR_H
#define PI4HOME_VERSION_TEXT_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_VERSION_TEXT_SENSOR

#include "pi4home/component.h"
#include "pi4home/text_sensor/text_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace text_sensor {

class VersionTextSensor : public TextSensor, public Component {
 public:
  explicit VersionTextSensor(const std::string &name);
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  std::string icon() override;
  std::string unique_id() override;
};

}  // namespace text_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_VERSION_TEXT_SENSOR

#endif  // PI4HOME_VERSION_TEXT_SENSOR_H
