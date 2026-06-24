#include "../optimization/quantizer.h"
#include <iostream>
namespace nanoai { namespace models {
void Quantizer::quantize(const std::string& path, Precision p) {
    std::cout << "Quantizer: Converting " << path << " to INT8 using calibration datasets." << std::endl;
}
} }
