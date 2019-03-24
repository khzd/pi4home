#ifndef PI4HOME_STEPPER_A4988_H
#define PI4HOME_STEPPER_A4988_H

#include "pi4home/defines.h"

#ifdef USE_A4988

#include "pi4home/component.h"
#include "pi4home/stepper/stepper.h"
#include "pi4home/esphal.h"

PI4HOME_NAMESPACE_BEGIN

namespace stepper {

class A4988 : public Stepper, public Component {
 public:
  A4988(GPIOPin *step_pin, GPIOPin *dir_pin);
  void set_sleep_pin(const GPIOOutputPin &sleep_pin);
  void setup() override;
  void dump_config() override;
  void loop() override;
  float get_setup_priority() const override;

 protected:
  GPIOPin *step_pin_;
  GPIOPin *dir_pin_;
  GPIOPin *sleep_pin_{nullptr};
  HighFrequencyLoopRequester high_freq_;
};

}  // namespace stepper

PI4HOME_NAMESPACE_END

#endif  // USE_A4988

#endif  // PI4HOME_STEPPER_A4988_H
