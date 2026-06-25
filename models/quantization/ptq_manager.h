#ifndef NANOAI_PTQ_MANAGER_H
#define NANOAI_PTQ_MANAGER_H

#include <string>
#include <vector>

namespace nanoai {
namespace models {

enum class CalibrationMethod { MIN_MAX, ENTROPY, PERCENTILE };

class PTQManager {
public:
    static PTQManager& getInstance();

    void runCalibration(const std::string& modelId, CalibrationMethod method);
    std::string generateQuantizedWeights(const std::string& modelId, int bits);
};

} // namespace models
} // namespace nanoai

#endif // NANOAI_PTQ_MANAGER_H
