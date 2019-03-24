#ifndef PI4HOME_SWITCH_SHUTDOWN_SWITCH_H
#define PI4HOME_SWITCH_SHUTDOWN_SWITCH_H

#include "pi4home/switch_/switch.h"
#include "pi4home/defines.h"

#ifdef USE_SHUTDOWN_SWITCH

PI4HOME_NAMESPACE_BEGIN

namespace switch_ {

/// A simple switch that will put the node into deep sleep indefinitely.
class ShutdownSwitch : public Switch, public Component {
 public:
  explicit ShutdownSwitch(const std::string &name);

  std::string icon() override;

  void dump_config() override;

 protected:
  void write_state(bool state) override;
};

}  // namespace switch_

PI4HOME_NAMESPACE_END

#endif  // USE_RESTART_SWITCH

#endif  // PI4HOME_SWITCH_SHUTDOWN_SWITCH_H
