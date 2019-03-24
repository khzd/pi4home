#include "pi4home/defines.h"

#ifdef USE_CUSTOM_COMPONENT

#include "pi4home/custom_component.h"
#include "pi4home/application.h"

PI4HOME_NAMESPACE_BEGIN

CustomComponentConstructor::CustomComponentConstructor(const std::function<std::vector<Component *>()> &init) {
  this->components_ = init();

  for (auto *comp : this->components_) {
    App.register_component(comp);
  }
}

Component *CustomComponentConstructor::get_component(int i) { return this->components_[i]; }

PI4HOME_NAMESPACE_END

#endif  // USE_CUSTOM_COMPONENT
