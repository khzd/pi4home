#ifndef PI4HOME_REMOTE_RAW_H
#define PI4HOME_REMOTE_RAW_H

#include "pi4home/defines.h"

#ifdef USE_REMOTE

#include "pi4home/remote/remote_receiver.h"
#include "pi4home/remote/remote_transmitter.h"

PI4HOME_NAMESPACE_BEGIN

namespace remote {

#ifdef USE_REMOTE_TRANSMITTER
class RawTransmitter : public RemoteTransmitter {
 public:
  RawTransmitter(const std::string &name, const int32_t *data, size_t len, uint32_t carrier_frequency = 0);

  void to_data(RemoteTransmitData *data) override;

 protected:
  const int32_t *data_;
  size_t len_;
  uint32_t carrier_frequency_{0};
};
#endif

#ifdef USE_REMOTE_RECEIVER
class RawReceiver : public RemoteReceiver {
 public:
  RawReceiver(const std::string &name, const int32_t *data, size_t len);

 protected:
  bool matches(RemoteReceiveData *data) override;

  const int32_t *data_;
  size_t len_;
};

class RawDumper : public RemoteReceiveDumper {
 public:
  bool dump(RemoteReceiveData *data) override;

  bool is_secondary() override;
};
#endif

}  // namespace remote

PI4HOME_NAMESPACE_END

#endif  // USE_REMOTE

#endif  // PI4HOME_REMOTE_RAW_H
