#ifndef NANOAI_CONVERTER_H
#define NANOAI_CONVERTER_H

#include "nanoai/model_conversion.h"
#include <string>

namespace nanoai {

class ModelConverter {
public:
    static bool convert(const std::string& inputPath,
                       const std::string& outputPath,
                       const ConversionConfig& config);
};

} // namespace nanoai

#endif // NANOAI_CONVERTER_H
