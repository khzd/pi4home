#ifndef PI4HOME_HMC_5883_L_H
#define PI4HOME_HMC_5883_L_H

#include "pi4home/defines.h"

#ifdef USE_HMC5883L

#include "pi4home/sensor/sensor.h"
#include "pi4home/i2c_component.h"

PI4HOME_NAMESPACE_BEGIN

namespace sensor {

enum HMC5883LRange {
  HMC5883L_RANGE_88_UT = 0b000,
  HMC5883L_RANGE_130_UT = 0b001,
  HMC5883L_RANGE_190_UT = 0b010,
  HMC5883L_RANGE_250_UT = 0b011,
  HMC5883L_RANGE_400_UT = 0b100,
  HMC5883L_RANGE_470_UT = 0b101,
  HMC5883L_RANGE_560_UT = 0b110,
  HMC5883L_RANGE_810_UT = 0b111,
};

using HMC5883LFieldStrengthSensor = EmptyPollingParentSensor<1, ICON_MAGNET, UNIT_UT>;
using HMC5883LHeadingSensor = EmptyPollingParentSensor<1, ICON_SCREEN_ROTATION, UNIT_DEGREES>;

class HMC5883LComponent : public PollingComponent, public I2CDevice {
 public:
  HMC5883LComponent(I2CComponent *parent, uint32_t update_interval = 60000);

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

  HMC5883LFieldStrengthSensor *make_x_sensor(const std::string &name);
  HMC5883LFieldStrengthSensor *make_y_sensor(const std::string &name);
  HMC5883LFieldStrengthSensor *make_z_sensor(const std::string &name);
  HMC5883LHeadingSensor *make_heading_sensor(const std::string &name);

  void set_range(HMC5883LRange range);

 protected:
  HMC5883LRange range_{HMC5883L_RANGE_130_UT};
  HMC5883LFieldStrengthSensor *x_sensor_;
  HMC5883LFieldStrengthSensor *y_sensor_;
  HMC5883LFieldStrengthSensor *z_sensor_;
  HMC5883LHeadingSensor *heading_sensor_;
  enum ErrorCode {
    NONE = 0,
    COMMUNICATION_FAILED,
    ID_REGISTERS,
  } error_code_;
};

}  // namespace sensor

PI4HOME_NAMESPACE_END

#endif  // USE_HMC5883L

#endif  // PI4HOME_HMC_5883_L_H
