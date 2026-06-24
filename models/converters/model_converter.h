#ifndef NANOAI_MODEL_CONVERTER_H
#define NANOAI_MODEL_CONVERTER_H

#include <string>

namespace nanoai {
namespace models {

class ModelConverter {
public:
    static bool convertToGGUF(const std::string& inputPath, const std::string& outputPath);
    static bool convertToONNX(const std::string& inputPath, const std::string& outputPath);
};

} }
#endif
