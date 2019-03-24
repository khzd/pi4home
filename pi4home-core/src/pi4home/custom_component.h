#ifndef PI4HOME_CUSTOM_COMPONENT_H
#define PI4HOME_CUSTOM_COMPONENT_H

#include "pi4home/defines.h"

#ifdef USE_CUSTOM_COMPONENT

#include "pi4home/component.h"

PI4HOME_NAMESPACE_BEGIN

class CustomComponentConstructor {
 public:
  CustomComponentConstructor(const std::function<std::vector<Component *>()> &init);

  Component *get_component(int i);

 protected:
  std::vector<Component *> components_;
};

PI4HOME_NAMESPACE_END

#endif  // USE_CUSTOM_COMPONENT

#endif  // PI4HOME_CUSTOM_COMPONENT_H
