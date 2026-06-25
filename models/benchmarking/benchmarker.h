#ifndef NANOAI_MODEL_BENCHMARKER_H
#define NANOAI_MODEL_BENCHMARKER_H

#include <string>
#include <vector>

namespace nanoai {
namespace models {

struct ModelPerfStats {
    float avgLatencyMs;
    float peakThroughput;
    size_t peakMemoryUsage;
    float reliabilityScore;
};

class Benchmarker {
public:
    static ModelPerfStats runBenchmark(const std::string& modelId, int iterations = 100);
    static void logDetailedReport(const std::string& modelId);
};

} // namespace models
} // namespace nanoai

#endif // NANOAI_MODEL_BENCHMARKER_H
