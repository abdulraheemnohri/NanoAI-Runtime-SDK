#ifndef NANOAI_MODEL_CONVERSION_H
#define NANOAI_MODEL_CONVERSION_H

#include <string>

namespace nanoai {

enum class QuantizationType {
    NONE, // FP32
    FP16,
    INT8,
    INT4
};

struct ConversionConfig {
    QuantizationType quantization;
    bool enablePruning; // Even if not in core issue, useful for internal tracking
    bool optimizeForNPU;
};

} // namespace nanoai

#endif // NANOAI_MODEL_CONVERSION_H
