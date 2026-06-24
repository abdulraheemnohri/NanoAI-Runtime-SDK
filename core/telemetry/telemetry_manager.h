#ifndef NANOAI_TELEMETRY_MANAGER_H
#define NANOAI_TELEMETRY_MANAGER_H
#include <string>
namespace nanoai { namespace telemetry {
class TelemetryManager {
public:
    static TelemetryManager& getInstance();
    std::string getFullReport();
};
} }
#endif
