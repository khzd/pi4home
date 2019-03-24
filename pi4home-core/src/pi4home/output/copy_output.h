#ifndef PI4HOME_CORE_OUTPUT_COPY_OUTPUT_H
#define PI4HOME_CORE_OUTPUT_COPY_OUTPUT_H

#include "pi4home/defines.h"

#ifdef USE_COPY_OUTPUT

#include "pi4home/component.h"
#include "pi4home/output/binary_output.h"
#include "pi4home/output/float_output.h"

PI4HOME_NAMESPACE_BEGIN

namespace output {

class BinaryCopyOutput : public BinaryOutput {
 public:
  BinaryCopyOutput(const std::vector<BinaryOutput *> &outputs);

 protected:
  std::vector<BinaryOutput *> outputs_;

  void write_state(bool state) override;
};

class FloatCopyOutput : public FloatOutput {
 public:
  FloatCopyOutput(const std::vector<FloatOutput *> &outputs);

 protected:
  std::vector<FloatOutput *> outputs_;

  void write_state(float state) override;
};

}  // namespace output

PI4HOME_NAMESPACE_END

#endif  // USE_COPY_OUTPUT

#endif  // PI4HOME_CORE_OUTPUT_COPY_OUTPUT_H
