#ifndef PI4HOME_REMOTE_LG_H
#define PI4HOME_REMOTE_LG_H

#include "pi4home/defines.h"

#ifdef USE_REMOTE

#include "pi4home/remote/remote_receiver.h"
#include "pi4home/remote/remote_transmitter.h"

PI4HOME_NAMESPACE_BEGIN

namespace remote {

#ifdef USE_REMOTE_TRANSMITTER
class LGTransmitter : public RemoteTransmitter {
 public:
  LGTransmitter(const std::string &name, uint32_t data, uint8_t nbits);

  void to_data(RemoteTransmitData *data) override;

 protected:
  uint32_t data_;
  uint8_t nbits_;
};

void encode_lg(RemoteTransmitData *data, uint32_t lg_data, uint8_t nbits);
#endif

#ifdef USE_REMOTE_RECEIVER
LGDecodeData decode_lg(RemoteReceiveData *data);

class LGReceiver : public RemoteReceiver {
 public:
  LGReceiver(const std::string &name, uint32_t data, uint8_t nbits);

 protected:
  bool matches(RemoteReceiveData *data) override;

  uint32_t data_;
  uint8_t nbits_;
};

class LGDumper : public RemoteReceiveDumper {
 public:
  bool dump(RemoteReceiveData *data) override;
};
#endif

}  // namespace remote

PI4HOME_NAMESPACE_END

#endif  // USE_REMOTE

#endif  // PI4HOME_REMOTE_LG_H
