#ifndef PI4HOME_STATUS_LED_H
#define PI4HOME_STATUS_LED_H

#include "pi4home/defines.h"

#ifdef USE_STATUS_LED

#include "pi4home/component.h"
#include "pi4home/esphal.h"

PI4HOME_NAMESPACE_BEGIN

class StatusLEDComponent : public Component {
 public:
  explicit StatusLEDComponent(GPIOPin *pin);

  void setup() override;
  void dump_config() override;
  void loop() override;
  float get_setup_priority() const override;
  float get_loop_priority() const override;

 protected:
  GPIOPin *pin_;
};

extern StatusLEDComponent *global_status_led;

PI4HOME_NAMESPACE_END

#endif  // USE_STATUS_LED

#endif  // PI4HOME_STATUS_LED_H
