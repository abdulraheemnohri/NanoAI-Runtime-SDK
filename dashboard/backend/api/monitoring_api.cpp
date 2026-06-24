#include "monitoring_api.h"
#include "../../../core/hardware/discovery/hal.h"
#include "../../../cluster/node_manager/cluster_manager.h"
#include "../../../core/telemetry/telemetry_manager.h"

namespace nanoai {
namespace dashboard {

MonitoringApi& MonitoringApi::getInstance() {
    static MonitoringApi instance;
    return instance;
}

std::string MonitoringApi::getHardwareStats() {
    return hal::HardwareAbstractionLayer::getInstance().generateCapabilityProfile();
}

std::string MonitoringApi::getClusterStatus() {
    return cluster::ClusterManager::getInstance().getNodes();
}

std::string MonitoringApi::getModelStats() {
    return telemetry::TelemetryManager::getInstance().getFullReport();
}

void MonitoringApi::logEvent(const std::string& level, const std::string& message) {
    // In a real system, this would push to a websocket or database
}

} // namespace dashboard
} // namespace nanoai
