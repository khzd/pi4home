#ifndef PI4HOME_REMOTE_REMOTE_PROTOCOL_H
#define PI4HOME_REMOTE_REMOTE_PROTOCOL_H

#include "pi4home/defines.h"

#ifdef USE_REMOTE

#include <vector>
#include "pi4home/component.h"
#include "pi4home/esphal.h"

#ifdef ARDUINO_ARCH_ESP32
#include <driver/rmt.h>
#endif

PI4HOME_NAMESPACE_BEGIN

namespace remote {

class RemoteControlComponentBase {
 public:
  explicit RemoteControlComponentBase(GPIOPin *pin);

#ifdef ARDUINO_ARCH_ESP32
  void set_channel(rmt_channel_t channel);
  void set_clock_divider(uint8_t clock_divider);
#endif

 protected:
#ifdef ARDUINO_ARCH_ESP32
  uint32_t from_microseconds(uint32_t us);
  uint32_t to_microseconds(uint32_t ticks);
#endif

  GPIOPin *pin_;
#ifdef ARDUINO_ARCH_ESP32
  rmt_channel_t channel_{RMT_CHANNEL_0};
  uint8_t clock_divider_{80};
  esp_err_t error_code_{ESP_OK};
#endif
};

}  // namespace remote

PI4HOME_NAMESPACE_END

#endif  // USE_REMOTE

#endif  // PI4HOME_REMOTE_REMOTE_PROTOCOL_H
