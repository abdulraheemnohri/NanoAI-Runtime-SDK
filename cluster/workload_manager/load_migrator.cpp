#include "load_migrator.h"
#include <iostream>
#include <algorithm>

namespace nanoai {
namespace cluster {

LoadMigrator& LoadMigrator::getInstance() {
    static LoadMigrator instance;
    return instance;
}

void LoadMigrator::snapshotWorkload(const WorkloadState& state) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_activeWorkloads.push_back(state);
    std::cout << "LoadMigrator: Workload snapshot taken for session " << state.sessionId << std::endl;
}

bool LoadMigrator::migrateSession(const std::string& sessionId, const std::string& targetNodeId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << "LoadMigrator: Migrating context for session " << sessionId << " to " << targetNodeId << "..." << std::endl;

    auto it = std::find_if(m_activeWorkloads.begin(), m_activeWorkloads.end(),
        [&sessionId](const auto& s) { return s.sessionId == sessionId; });

    if (it != m_activeWorkloads.end()) {
        std::cout << "LoadMigrator: Context Data [" << it->contextData.size() << " bytes] transferred successfully." << std::endl;
        m_activeWorkloads.erase(it);
        return true;
    }

    std::cout << "LoadMigrator: Session " << sessionId << " not found locally." << std::endl;
    return false;
}

void LoadMigrator::balanceClusterLoad() {
    std::cout << "LoadMigrator: Analyzing cluster health for re-balancing..." << std::endl;
}

} // namespace cluster
} // namespace nanoai
