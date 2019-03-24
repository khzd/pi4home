#ifndef PI4HOME_SENSOR_ULTRASONIC_SENSOR_H
#define PI4HOME_SENSOR_ULTRASONIC_SENSOR_H

#include "pi4home/defines.h"

#ifdef USE_ULTRASONIC_SENSOR

#include "pi4home/sensor/sensor.h"
#include "pi4home/esphal.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

/// The speed of sound in air in meters per µs.
const float SPEED_OF_SOUND_M_PER_US = 0.000343f;

struct UltrasonicSensorStore {
  uint32_t triggered_at{0};
  bool has_triggered{false};
  uint32_t echo_at{0};
  bool has_echo{false};

  static void gpio_intr(UltrasonicSensorStore *arg);
};

class UltrasonicSensorComponent : public PollingSensorComponent {
 public:
  /** Construct the ultrasonic sensor with the specified trigger pin and echo pin.
   *
   * @param trigger_pin The trigger pin where pulses are sent to.
   * @param echo_pin The echo pin where the echo is listened for.
   * @param update_interval The interval in ms the sensor should check for new values.
   */
  UltrasonicSensorComponent(const std::string &name, GPIOPin *trigger_pin, GPIOPin *echo_pin,
                            uint32_t update_interval = 60000);

  /// Set the timeout for waiting for the echo in µs.
  void set_timeout_us(uint32_t timeout_us);

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  /// Set up pins and register interval.
  void setup() override;
  void dump_config() override;

  void update() override;
  void loop() override;

  std::string unit_of_measurement() override;
  std::string icon() override;
  int8_t accuracy_decimals() override;

  float get_setup_priority() const override;

  /// Set the time in µs the trigger pin should be enabled for in µs, defaults to 10µs (for HC-SR04)
  void set_pulse_time_us(uint32_t pulse_time_us);

 protected:
  /// Helper function to convert the specified echo duration in µs to meters.
  static float us_to_m(uint32_t us);
  /// Helper function to convert the specified distance in meters to the echo duration in µs.

  GPIOPin *trigger_pin_;
  GPIOPin *echo_pin_;
  uint32_t timeout_us_{58309};  /// 10 meters.
  uint32_t pulse_time_us_{10};
  UltrasonicSensorStore store_;
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_ULTRASONIC_SENSOR

#endif  // PI4HOME_SENSOR_ULTRASONIC_SENSOR_H
