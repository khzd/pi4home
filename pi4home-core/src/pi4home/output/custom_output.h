#ifndef PI4HOME_OUTPUT_CUSTOM_OUTPUT_H
#define PI4HOME_OUTPUT_CUSTOM_OUTPUT_H

#include "pi4home/defines.h"

#ifdef USE_CUSTOM_OUTPUT

#include "pi4home/output/binary_output.h"
#include "pi4home/output/float_output.h"

PI4HOME_NAMESPACE_BEGIN

namespace output {

class CustomBinaryOutputConstructor {
 public:
  CustomBinaryOutputConstructor(std::function<std::vector<BinaryOutput *>()> init);

  BinaryOutput *get_output(int i);

 protected:
  std::vector<BinaryOutput *> outputs_;
};

class CustomFloatOutputConstructor {
 public:
  CustomFloatOutputConstructor(std::function<std::vector<FloatOutput *>()> init);

  FloatOutput *get_output(int i);

 protected:
  std::vector<FloatOutput *> outputs_;
};

}  // namespace output

PI4HOME_NAMESPACE_END

#endif  // USE_CUSTOM_OUTPUT

#endif  // PI4HOME_OUTPUT_CUSTOM_OUTPUT_H
