#ifndef PI4HOME_REMOTE_PANASONIC_H
#define PI4HOME_REMOTE_PANASONIC_H

#include "pi4home/defines.h"

#ifdef USE_REMOTE

#include "pi4home/remote/remote_receiver.h"
#include "pi4home/remote/remote_transmitter.h"

PI4HOME_NAMESPACE_BEGIN

namespace remote {

#ifdef USE_REMOTE_TRANSMITTER
class PanasonicTransmitter : public RemoteTransmitter {
 public:
  PanasonicTransmitter(const std::string &name, uint16_t address, uint32_t command);

  void to_data(RemoteTransmitData *data) override;

 protected:
  uint16_t address_;
  uint32_t command_;
};

void encode_panasonic(RemoteTransmitData *data, uint16_t address, uint32_t command);
#endif

#ifdef USE_REMOTE_RECEIVER
PanasonicDecodeData decode_panasonic(RemoteReceiveData *data);

class PanasonicReceiver : public RemoteReceiver {
 public:
  PanasonicReceiver(const std::string &name, uint16_t address, uint32_t command);

 protected:
  bool matches(RemoteReceiveData *data) override;

  uint16_t address_;
  uint32_t command_;
};

class PanasonicDumper : public RemoteReceiveDumper {
 public:
  bool dump(RemoteReceiveData *data) override;
};
#endif

}  // namespace remote

PI4HOME_NAMESPACE_END

#endif  // USE_REMOTE

#endif  // PI4HOME_REMOTE_PANASONIC_H
