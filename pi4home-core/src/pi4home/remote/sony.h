#ifndef PI4HOME_REMOTE_SONY_H
#define PI4HOME_REMOTE_SONY_H

#include "pi4home/defines.h"

#ifdef USE_REMOTE

#include "pi4home/remote/remote_receiver.h"
#include "pi4home/remote/remote_transmitter.h"

PI4HOME_NAMESPACE_BEGIN

namespace remote {

#ifdef USE_REMOTE_TRANSMITTER
class SonyTransmitter : public RemoteTransmitter {
 public:
  SonyTransmitter(const std::string &name, uint32_t data, uint8_t nbits);

  void to_data(RemoteTransmitData *data) override;

 protected:
  uint32_t data_;
  uint8_t nbits_;
};

void encode_sony(RemoteTransmitData *data, uint32_t sony_data, uint8_t nbits);
#endif

#ifdef USE_REMOTE_RECEIVER
SonyDecodeData decode_sony(RemoteReceiveData *data);

class SonyReceiver : public RemoteReceiver {
 public:
  SonyReceiver(const std::string &name, uint32_t data, uint8_t nbits);

 protected:
  bool matches(RemoteReceiveData *data) override;

  uint32_t data_;
  uint8_t nbits_;
};

class SonyDumper : public RemoteReceiveDumper {
 public:
  bool dump(RemoteReceiveData *data) override;
};
#endif

}  // namespace remote

PI4HOME_NAMESPACE_END

#endif  // USE_REMOTE

#endif  // PI4HOME_REMOTE_SONY_H
