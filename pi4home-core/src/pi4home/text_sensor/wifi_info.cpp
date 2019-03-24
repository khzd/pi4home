#include "pi4home/defines.h"

#ifdef USE_WIFI_INFO_TEXT_SENSOR

#include "pi4home/text_sensor/wifi_info.h"
#include "pi4home/wifi_component.h"
#include "pi4home/log.h"

PI4HOME_NAMESPACE_BEGIN

namespace text_sensor {

static const char *TAG = "text_sensor.wifi_info";

void IPAddressWiFiInfo::loop() {
  IPAddress ip = WiFi.localIP();
  if (ip != this->last_ip_) {
    this->last_ip_ = ip;
    this->publish_state(ip.toString().c_str());
  }
}
IPAddressWiFiInfo::IPAddressWiFiInfo(const std::string &name) : TextSensor(name) {}

void SSIDWiFiInfo::loop() {
  const char *ssid = WiFi.SSID().c_str();
  if (this->last_ssid_ != ssid) {
    this->last_ssid_ = ssid;
    this->publish_state(ssid);
  }
}
SSIDWiFiInfo::SSIDWiFiInfo(const std::string &name) : TextSensor(name) {}

void BSSIDWiFiInfo::loop() {
  const char *bssid = WiFi.BSSIDstr().c_str();
  if (this->last_bssid_ != bssid) {
    this->last_bssid_ = bssid;
    this->publish_state(bssid);
  }
}
BSSIDWiFiInfo::BSSIDWiFiInfo(const std::string &name) : TextSensor(name) {}

}  // namespace text_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_WIFI_INFO_TEXT_SENSOR
