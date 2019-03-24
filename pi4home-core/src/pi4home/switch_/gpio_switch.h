#ifndef PI4HOME_SWITCH_GPIO_SWITCH_H
#define PI4HOME_SWITCH_GPIO_SWITCH_H

#include "pi4home/defines.h"

#ifdef USE_GPIO_SWITCH

#include "pi4home/component.h"
#include "pi4home/esphal.h"
#include "pi4home/switch_/switch.h"

PI4HOME_NAMESPACE_BEGIN

namespace switch_ {

enum GPIOSwitchRestoreMode {
  GPIO_SWITCH_RESTORE_DEFAULT_OFF,
  GPIO_SWITCH_RESTORE_DEFAULT_ON,
  GPIO_SWITCH_ALWAYS_OFF,
  GPIO_SWITCH_ALWAYS_ON,
};

class GPIOSwitch : public Switch, public Component {
 public:
  GPIOSwitch(const std::string &name, GPIOPin *pin);

  void set_restore_mode(GPIOSwitchRestoreMode restore_mode);

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  float get_setup_priority() const override;

  void setup() override;
  void dump_config() override;
  void set_interlock(const std::vector<Switch *> &interlock);

 protected:
  void write_state(bool state) override;

  GPIOPin *const pin_;
  GPIOSwitchRestoreMode restore_mode_{GPIO_SWITCH_RESTORE_DEFAULT_OFF};
  std::vector<Switch *> interlock_;
};

}  // namespace switch_

PI4HOME_NAMESPACE_END

#endif  // USE_GPIO_SWITCH

#endif  // PI4HOME_SWITCH_GPIO_SWITCH_H
