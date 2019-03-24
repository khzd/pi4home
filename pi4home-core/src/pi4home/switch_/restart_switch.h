#ifndef PI4HOME_RESTART_SWITCH_H
#define PI4HOME_RESTART_SWITCH_H

#include "pi4home/switch_/switch.h"
#include "pi4home/defines.h"

#ifdef USE_RESTART_SWITCH

PI4HOME_NAMESPACE_BEGIN

namespace switch_ {

/// A simple switch that restarts the device when triggered.
class RestartSwitch : public Switch, public Component {
 public:
  explicit RestartSwitch(const std::string &name);

  std::string icon() override;

  void dump_config() override;

 protected:
  void write_state(bool state) override;
};

}  // namespace switch_

PI4HOME_NAMESPACE_END

#endif  // USE_RESTART_SWITCH

#endif  // PI4HOME_RESTART_SWITCH_H
