#ifndef NANOAI_HARDWARE_MONITOR_H
#define NANOAI_HARDWARE_MONITOR_H

#include <string>
#include <map>

namespace nanoai {
namespace hardware {

struct HardwareStats {
    float cpuUsage;
    float gpuUsage;
    float npuUsage;
    float temperature;
    float powerDraw;
};

class HardwareMonitor {
public:
    static HardwareMonitor& getInstance();
    HardwareStats getCurrentStats();
    void logTelemetry();
};

} }
#endif
