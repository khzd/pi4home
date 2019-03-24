#ifndef PI4HOME_COVER_TEMPLATE_COVER_H
#define PI4HOME_COVER_TEMPLATE_COVER_H

#include "pi4home/defines.h"

#ifdef USE_TEMPLATE_COVER

#include "pi4home/cover/cover.h"
#include "pi4home/automation.h"

PI4HOME_NAMESPACE_BEGIN

namespace cover {

class TemplateCover : public Cover, public Component {
 public:
  explicit TemplateCover(const std::string &name);

  void set_state_lambda(std::function<optional<CoverState>()> &&f);
  Trigger<> *get_open_trigger() const;
  Trigger<> *get_close_trigger() const;
  Trigger<> *get_stop_trigger() const;
  void set_optimistic(bool optimistic);
  void set_assumed_state(bool assumed_state);

  void loop() override;
  void dump_config() override;

  float get_setup_priority() const override;

 protected:
  void write_command(CoverCommand command) override;
  bool assumed_state() override;

  optional<std::function<optional<CoverState>()>> f_;
  bool assumed_state_{false};
  bool optimistic_{false};
  Trigger<> *open_trigger_;
  Trigger<> *close_trigger_;
  Trigger<> *stop_trigger_;
  Trigger<> *prev_trigger_{nullptr};
};

}  // namespace cover

PI4HOME_NAMESPACE_END

#endif  // USE_TEMPLATE_COVER

#endif  // PI4HOME_COVER_TEMPLATE_COVER_H
