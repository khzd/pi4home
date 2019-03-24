#ifndef PI4HOME_TEXT_SENSOR_TEMPLATE_TEXT_SENSOR_H
#define PI4HOME_TEXT_SENSOR_TEMPLATE_TEXT_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_TEMPLATE_TEXT_SENSOR

#include "pi4home/text_sensor/text_sensor.h"
#include "pi4home/helpers.h"

PI4HOME_NAMESPACE_BEGIN

namespace text_sensor {

class TemplateTextSensor : public TextSensor, public PollingComponent {
 public:
  TemplateTextSensor(const std::string &name, uint32_t update_interval = 60000);

  void set_template(std::function<optional<std::string>()> &&f);

  void update() override;

  float get_setup_priority() const override;

  void dump_config() override;

 protected:
  optional<std::function<optional<std::string>()>> f_{};
};

}  // namespace text_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_TEMPLATE_TEXT_SENSOR

#endif  // PI4HOME_TEXT_SENSOR_TEMPLATE_TEXT_SENSOR_H
