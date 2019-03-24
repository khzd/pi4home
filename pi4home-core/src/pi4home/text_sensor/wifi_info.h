#ifndef PI4HOME_CORE_TEXT_SENSOR_WIFI_INFO_H
#define PI4HOME_CORE_TEXT_SENSOR_WIFI_INFO_H

#include "pi4home/defines.h"

#ifdef USE_WIFI_INFO_TEXT_SENSOR

#include "pi4home/component.h"
#include "pi4home/text_sensor/text_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace text_sensor {

class IPAddressWiFiInfo : public Component, public TextSensor {
 public:
  IPAddressWiFiInfo(const std::string &name);
  void loop() override;

 protected:
  IPAddress last_ip_;
};

class SSIDWiFiInfo : public Component, public TextSensor {
 public:
  SSIDWiFiInfo(const std::string &name);
  void loop() override;

 protected:
  std::string last_ssid_;
};

class BSSIDWiFiInfo : public Component, public TextSensor {
 public:
  BSSIDWiFiInfo(const std::string &name);
  void loop() override;

 protected:
  std::string last_bssid_;
};

}  // namespace text_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_WIFI_INFO_TEXT_SENSOR

#endif  // PI4HOME_CORE_TEXT_SENSOR_WIFI_INFO_H
