#include "hardware_monitor.h"
#include <iostream>
#include <random>

namespace nanoai {
namespace hardware {

HardwareMonitor& HardwareMonitor::getInstance() {
    static HardwareMonitor instance;
    return instance;
}

HardwareStats HardwareMonitor::getCurrentStats() {
    // Simulated real-time sensor reading
    return {
        15.0f + (rand() % 10),
        45.0f + (rand() % 20),
        88.0f + (rand() % 5),
        42.5f + (rand() % 10) / 10.0f,
        150.0f + (rand() % 50)
    };
}

void HardwareMonitor::logTelemetry() {
    auto stats = getCurrentStats();
    std::cout << "[MONITOR] CPU: " << stats.cpuUsage << "%, GPU: " << stats.gpuUsage
              << "%, NPU: " << stats.npuUsage << "%, Temp: " << stats.temperature << "C" << std::endl;
}

} }
