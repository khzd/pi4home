#ifndef PI4HOME_CUSTOM_SWITCH_H
#define PI4HOME_CUSTOM_SWITCH_H

#include "pi4home/defines.h"

#ifdef USE_CUSTOM_SWITCH

#include "pi4home/switch_/switch.h"
#include "pi4home/component.h"

PI4HOME_NAMESPACE_BEGIN

namespace switch_ {

class CustomSwitchConstructor : public Component {
 public:
  CustomSwitchConstructor(std::function<std::vector<Switch *>()> init);

  Switch *get_switch(int i);

  void dump_config() override;

 protected:
  std::vector<Switch *> switches_;
};

}  // namespace switch_

PI4HOME_NAMESPACE_END

#endif  // USE_CUSTOM_SWITCH

#endif  // PI4HOME_CUSTOM_SWITCH_H
