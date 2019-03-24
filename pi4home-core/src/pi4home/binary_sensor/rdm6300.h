#ifndef PI4HOME_RDM_6300_H
#define PI4HOME_RDM_6300_H

#include "pi4home/defines.h"

#ifdef USE_RDM6300

#include "pi4home/uart_component.h"
#include "pi4home/binary_sensor/binary_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace binary_sensor {

class RDM6300BinarySensor;

class RDM6300Component : public Component, public UARTDevice {
 public:
  RDM6300Component(UARTComponent *parent);

  void loop() override;

  RDM6300BinarySensor *make_card(const std::string &name, uint32_t id);

  float get_setup_priority() const override;

 protected:
  int8_t read_state_{-1};
  uint8_t buffer_[6];
  std::vector<RDM6300BinarySensor *> cards_;
  uint32_t last_id_{0};
};

class RDM6300BinarySensor : public BinarySensor {
 public:
  RDM6300BinarySensor(const std::string &name, uint32_t id);

  bool process(uint32_t id);

 protected:
  uint32_t id_;
};

}  // namespace binary_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_RDM6300

#endif  // PI4HOME_RDM_6300_H
