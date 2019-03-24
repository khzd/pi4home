#ifndef PI4HOME_HOMEASSISTANT_TIME_H
#define PI4HOME_HOMEASSISTANT_TIME_H

#include "pi4home/defines.h"

#ifdef USE_HOMEASSISTANT_TIME

#include "pi4home/component.h"
#include "pi4home/time/rtc_component.h"
#include "pi4home/api/api_message.h"

PI4HOME_NAMESPACE_BEGIN

namespace time {

class HomeAssistantTime : public RealTimeClockComponent {
 public:
  void setup() override;
  void dump_config() override;
  void set_epoch_time(uint32_t epoch);
  float get_setup_priority() const override;

 protected:
};

extern HomeAssistantTime *global_homeassistant_time;

class GetTimeResponse : public api::APIMessage {
 public:
  bool decode_32bit(uint32_t field_id, uint32_t value) override;
  api::APIMessageType message_type() const override;
};

}  // namespace time

PI4HOME_NAMESPACE_END

#endif  // USE_HOMEASSISTANT_TIME

#endif  // PI4HOME_HOMEASSISTANT_TIME_H
