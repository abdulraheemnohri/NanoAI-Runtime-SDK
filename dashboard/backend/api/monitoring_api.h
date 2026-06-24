#ifndef NANOAI_MONITORING_API_H
#define NANOAI_MONITORING_API_H

#include <string>

namespace nanoai {
namespace dashboard {

class MonitoringApi {
public:
    static MonitoringApi& getInstance();

    std::string getHardwareStats();
    std::string getClusterStatus();
    std::string getModelStats();

    void logEvent(const std::string& level, const std::string& message);
};

} // namespace dashboard
} // namespace nanoai

#endif // NANOAI_MONITORING_API_H
