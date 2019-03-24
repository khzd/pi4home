#ifndef PI4HOME_STATUS_BINARY_SENSOR_H
#define PI4HOME_STATUS_BINARY_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_STATUS_BINARY_SENSOR

#include "pi4home/binary_sensor/binary_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace binary_sensor {

/** Simple binary sensor that reports the online/offline state of the node using MQTT
 *
 * Most of the magic doesn't happen here, but in Application.make_status_binary_sensor.
 */
class StatusBinarySensor : public BinarySensor, public Component {
 public:
  /// Construct the status binary sensor
  explicit StatusBinarySensor(const std::string &name);

  void loop() override;

  void setup() override;
  void dump_config() override;

  float get_setup_priority() const override;

  bool is_status_binary_sensor() const override;

 protected:
  /// "connectivity" device class.
  std::string device_class() override;
  bool last_status_{false};
};

}  // namespace binary_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_STATUS_BINARY_SENSOR

#endif  // PI4HOME_STATUS_BINARY_SENSOR_H
