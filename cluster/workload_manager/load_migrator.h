#ifndef NANOAI_LOAD_MIGRATOR_H
#define NANOAI_LOAD_MIGRATOR_H

#include <string>
#include <vector>
#include <mutex>

namespace nanoai {
namespace cluster {

struct WorkloadState {
    std::string sessionId;
    std::string modelId;
    std::string contextData;
};

class LoadMigrator {
public:
    static LoadMigrator& getInstance();

    bool migrateSession(const std::string& sessionId, const std::string& targetNodeId);
    void balanceClusterLoad();

    void snapshotWorkload(const WorkloadState& state);

private:
    LoadMigrator() = default;
    std::vector<WorkloadState> m_activeWorkloads;
    std::mutex m_mutex;
};

} // namespace cluster
} // namespace nanoai

#endif // NANOAI_LOAD_MIGRATOR_H
