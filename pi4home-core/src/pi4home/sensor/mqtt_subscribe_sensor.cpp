#include "pi4home/defines.h"

#ifdef USE_MQTT_SUBSCRIBE_SENSOR

#include "pi4home/sensor/mqtt_subscribe_sensor.h"
#include "pi4home/mqtt/mqtt_client_component.h"
#include "pi4home/log.h"
#include <utility>
#include <cstdlib>

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

static const char *TAG = "sensor.mqtt_subscribe";

MQTTSubscribeSensor::MQTTSubscribeSensor(const std::string &name, std::string topic)
    : Sensor(name), topic_(std::move(topic)) {}
void MQTTSubscribeSensor::setup() {
  mqtt::global_mqtt_client->subscribe(this->topic_,
                                      [this](const std::string &topic, std::string payload) {
                                        auto val = parse_float(payload);
                                        if (!val.has_value()) {
                                          ESP_LOGW(TAG, "Can't convert '%s' to number!", payload.c_str());
                                          this->publish_state(NAN);
                                          return;
                                        }

                                        this->publish_state(*val);
                                      },
                                      this->qos_);
}

float MQTTSubscribeSensor::get_setup_priority() const { return setup_priority::MQTT_CLIENT - 1.0f; }
void MQTTSubscribeSensor::set_qos(uint8_t qos) { this->qos_ = qos; }
void MQTTSubscribeSensor::dump_config() {
  LOG_SENSOR("", "MQTT Subscribe", this);
  ESP_LOGCONFIG(TAG, "  Topic: %s", this->topic_.c_str());
}

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_MQTT_SUBSCRIBE_SENSOR
