#ifndef PI4HOME_LIGHT_LIGHT_TRANSFORMER_H
#define PI4HOME_LIGHT_LIGHT_TRANSFORMER_H

#include "pi4home/defines.h"

#ifdef USE_LIGHT

#include "pi4home/light/light_color_values.h"

PI4HOME_NAMESPACE_BEGIN

namespace light {

/// Base-class for all light color transformers, such as transitions or flashes.
class LightTransformer {
 public:
  LightTransformer(uint32_t start_time, uint32_t length, const LightColorValues &start_values,
                   const LightColorValues &target_values);

  LightTransformer() = delete;

  /// Whether this transformation is finished
  virtual bool is_finished();

  /// Whether the output needs to be written in every loop cycle.
  virtual bool is_continuous() = 0;

  /// This will be called to get the current values for output.
  virtual LightColorValues get_values() = 0;

  /// The values that should be reported to the front-end.
  virtual LightColorValues get_remote_values();

  /// The values that should be set after this transformation is complete.
  virtual LightColorValues get_end_values();

 protected:
  /// Get the completion of this transformer, 0 to 1.
  float get_progress_();

  const LightColorValues &get_start_values_() const;

  const LightColorValues &get_target_values_() const;

  uint32_t start_time_;
  uint32_t length_;
  LightColorValues start_values_;
  LightColorValues target_values_;
};

class LightTransitionTransformer : public LightTransformer {
 public:
  LightTransitionTransformer(uint32_t start_time, uint32_t length, const LightColorValues &start_values,
                             const LightColorValues &target_values);

  LightColorValues get_values() override;

  bool is_continuous() override;
};

class LightFlashTransformer : public LightTransformer {
 public:
  LightFlashTransformer(uint32_t start_time, uint32_t length, const LightColorValues &start_values,
                        const LightColorValues &target_values);

  LightColorValues get_values() override;

  LightColorValues get_end_values() override;

  bool is_continuous() override;
};

}  // namespace light

PI4HOME_NAMESPACE_END

#endif  // USE_LIGHT

#endif  // PI4HOME_LIGHT_LIGHT_TRANSFORMER_H
