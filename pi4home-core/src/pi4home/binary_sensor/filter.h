#ifndef PI4HOME_FILTER_H
#define PI4HOME_FILTER_H

#include "pi4home/defines.h"

#ifdef USE_BINARY_SENSOR

#include "pi4home/binary_sensor/binary_sensor.h"

PI4HOME_NAMESPACE_BEGIN

namespace binary_sensor {

class BinarySensor;

class Filter {
 public:
  virtual optional<bool> new_value(bool value, bool is_initial) = 0;

  void input(bool value, bool is_initial);

  void output(bool value, bool is_initial);

 protected:
  friend BinarySensor;

  Filter *next_{nullptr};
  BinarySensor *parent_{nullptr};
  Deduplicator<bool> dedup_;
};

class DelayedOnFilter : public Filter, public Component {
 public:
  explicit DelayedOnFilter(uint32_t delay);

  optional<bool> new_value(bool value, bool is_initial) override;

  float get_setup_priority() const override;

 protected:
  uint32_t delay_;
};

class DelayedOffFilter : public Filter, public Component {
 public:
  explicit DelayedOffFilter(uint32_t delay);

  optional<bool> new_value(bool value, bool is_initial) override;

  float get_setup_priority() const override;

 protected:
  uint32_t delay_;
};

class InvertFilter : public Filter {
 public:
  optional<bool> new_value(bool value, bool is_initial) override;
};

class LambdaFilter : public Filter {
 public:
  explicit LambdaFilter(const std::function<optional<bool>(bool)> &f);

  optional<bool> new_value(bool value, bool is_initial) override;

 protected:
  std::function<optional<bool>(bool)> f_;
};

class UniqueFilter : public Filter {
 public:
  optional<bool> new_value(bool value, bool is_initial) override;

 protected:
  optional<bool> last_value_{};
};

}  // namespace binary_sensor

PI4HOME_NAMESPACE_END

#endif  // USE_BINARY_SENSOR

#endif  // PI4HOME_FILTER_H
