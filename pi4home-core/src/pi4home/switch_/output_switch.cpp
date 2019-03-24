#include "pi4home/defines.h"

#ifdef USE_OUTPUT_SWITCH

#include "pi4home/switch_/output_switch.h"
#include "pi4home/log.h"

PI4HOME_NAMESPACE_BEGIN

namespace switch_ {

static const char *TAG = "switch.output";

OutputSwitch::OutputSwitch(const std::string &name, output::BinaryOutput *output) : Switch(name), output_(output) {}
void OutputSwitch::write_state(bool state) {
  if (state) {
    this->output_->turn_on();
  } else {
    this->output_->turn_off();
  }
  this->publish_state(state);
}
void OutputSwitch::setup() {
  auto restored = this->get_initial_state();
  if (!restored.has_value())
    return;

  if (*restored) {
    this->turn_on();
  } else {
    this->turn_off();
  }
}
float OutputSwitch::get_setup_priority() const { return setup_priority::HARDWARE; }
void OutputSwitch::dump_config() { LOG_SWITCH("", "Output Switch", this); }

}  // namespace switch_

PI4HOME_NAMESPACE_END

#endif  // USE_OUTPUT_SWITCH
