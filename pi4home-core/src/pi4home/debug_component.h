#ifndef PI4HOME_DEBUG_COMPONENT_H
#define PI4HOME_DEBUG_COMPONENT_H

#include "pi4home/defines.h"

#ifdef USE_DEBUG_COMPONENT

#include "pi4home/component.h"

PI4HOME_NAMESPACE_BEGIN

/// The debug component prints out debug information like free heap size on startup.
class DebugComponent : public Component {
 public:
  void setup() override;
  void loop() override;
  float get_setup_priority() const override;

 protected:
  uint32_t free_heap_{};
};

PI4HOME_NAMESPACE_END

#endif  // USE_DEBUG_COMPONENT

#endif  // PI4HOME_DEBUG_COMPONENT_H
