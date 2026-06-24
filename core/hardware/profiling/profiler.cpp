#include "profiler.h"
#include <iostream>

namespace nanoai {
namespace hardware {

void Profiler::profileDevice(const std::string& deviceId) {
    std::cout << "[PROFILER] Analyzing latency/throughput for " << deviceId << "..." << std::endl;
}

} }
