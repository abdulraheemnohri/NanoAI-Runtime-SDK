#ifndef NANOAI_WEIGHT_COMPRESSOR_H
#define NANOAI_WEIGHT_COMPRESSOR_H

#include <string>

namespace nanoai {
namespace memory {

class WeightCompressor {
public:
    static std::string compress(const std::string& data);
    static std::string decompress(const std::string& data);
};

} // namespace memory
} // namespace nanoai

#endif // NANOAI_WEIGHT_COMPRESSOR_H
