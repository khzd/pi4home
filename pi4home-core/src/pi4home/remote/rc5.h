#ifndef PI4HOME_REMOTE_RC5_H
#define PI4HOME_REMOTE_RC5_H

#include "pi4home/defines.h"

#ifdef USE_REMOTE

#include "pi4home/remote/remote_receiver.h"
#include "pi4home/remote/remote_transmitter.h"

PI4HOME_NAMESPACE_BEGIN

namespace remote {

#ifdef USE_REMOTE_TRANSMITTER
class RC5Transmitter : public RemoteTransmitter {
 public:
  RC5Transmitter(const std::string &name, uint8_t address, uint8_t command);

  void to_data(RemoteTransmitData *data) override;

 protected:
  uint8_t address_;
  uint8_t command_;
  bool toggle_{false};
};

void encode_rc5(RemoteTransmitData *data, uint8_t address, uint8_t command, bool toggle);
#endif

#ifdef USE_REMOTE_RECEIVER
RC5DecodeData decode_rc5(RemoteReceiveData *data);

class RC5Receiver : public RemoteReceiver {
 public:
  RC5Receiver(const std::string &name, uint8_t address, uint8_t command);

 protected:
  bool matches(RemoteReceiveData *data) override;

  uint8_t address_;
  uint8_t command_;
};

class RC5Dumper : public RemoteReceiveDumper {
 public:
  bool dump(RemoteReceiveData *data) override;
};
#endif

}  // namespace remote

PI4HOME_NAMESPACE_END

#endif  // USE_REMOTE

#endif  // PI4HOME_REMOTE_RC5_H
