#ifndef NANOAI_QUANTIZER_H
#define NANOAI_QUANTIZER_H

#include <string>

namespace nanoai {
namespace models {

enum class Precision { FP32, FP16, INT8, INT4 };

class Quantizer {
public:
    static void quantize(const std::string& modelPath, Precision target);
};

} }
#endif
