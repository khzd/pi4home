#ifndef PI4HOME_LIST_ENTITIES_H
#define PI4HOME_LIST_ENTITIES_H

#include "pi4home/defines.h"

#ifdef USE_API

#include "pi4home/component.h"
#include "pi4home/api/api_message.h"

PI4HOME_NAMESPACE_BEGIN

namespace api {

class ListEntitiesRequest : public APIMessage {
 public:
  APIMessageType message_type() const override;
};

class APIConnection;

class ListEntitiesIterator : public ComponentIterator {
 public:
  ListEntitiesIterator(APIServer *server, APIConnection *client);
#ifdef USE_BINARY_SENSOR
  bool on_binary_sensor(binary_sensor::BinarySensor *binary_sensor) override;
#endif
#ifdef USE_COVER
  bool on_cover(cover::Cover *cover) override;
#endif
#ifdef USE_FAN
  bool on_fan(fan::FanState *fan) override;
#endif
#ifdef USE_LIGHT
  bool on_light(light::LightState *light) override;
#endif
#ifdef USE_SENSOR
  bool on_sensor(sensor::Sensor *sensor) override;
#endif
#ifdef USE_SWITCH
  bool on_switch(switch_::Switch *a_switch) override;
#endif
#ifdef USE_TEXT_SENSOR
  bool on_text_sensor(text_sensor::TextSensor *text_sensor) override;
#endif
  bool on_service(UserServiceDescriptor *service) override;
#ifdef USE_ESP32_CAMERA
  bool on_camera(ESP32Camera *camera) override;
#endif
  bool on_end() override;

 protected:
  APIConnection *client_;
};

}  // namespace api

PI4HOME_NAMESPACE_END

#include "pi4home/api/api_server.h"

#endif  // USE_API

#endif  // PI4HOME_LIST_ENTITIES_H
