#ifndef PI4HOME_SENSOR_TEMPLATE_SENSOR_H
#define PI4HOME_SENSOR_TEMPLATE_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_TEMPLATE_SENSOR

#include "pi4home/sensor/sensor.h"
#include "pi4home/helpers.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

class TemplateSensor : public PollingSensorComponent {
 public:
  TemplateSensor(const std::string &name, uint32_t update_interval = 60000);

  void set_template(std::function<optional<float>()> &&f);

  void update() override;

  void dump_config() override;

  float get_setup_priority() const override;

 protected:
  optional<std::function<optional<float>()>> f_;
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_TEMPLATE_SENSOR

#endif  // PI4HOME_SENSOR_TEMPLATE_SENSOR_H
