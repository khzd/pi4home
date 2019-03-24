#ifndef PI4HOME_UART_SWITCH_H
#define PI4HOME_UART_SWITCH_H

#include "pi4home/defines.h"

#ifdef USE_UART_SWITCH

#include "pi4home/switch_/switch.h"
#include "pi4home/uart_component.h"

PI4HOME_NAMESPACE_BEGIN

namespace switch_ {

class UARTSwitch : public Switch, public UARTDevice, public Component {
 public:
  UARTSwitch(UARTComponent *parent, const std::string &name, const std::vector<uint8_t> &data);

  void dump_config() override;

 protected:
  void write_state(bool state) override;
  std::vector<uint8_t> data_;
};

}  // namespace switch_

PI4HOME_NAMESPACE_END

#endif  // USE_UART_SWITCH

#endif  // PI4HOME_UART_SWITCH_H
