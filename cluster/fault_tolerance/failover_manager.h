#ifndef NANOAI_FAILOVER_MANAGER_H
#define NANOAI_FAILOVER_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <mutex>

namespace nanoai {
namespace cluster {

class FailoverManager {
public:
    static FailoverManager& getInstance();

    void monitorNode(const std::string& nodeId);
    void reportFailure(const std::string& nodeId);
    void reassignTasks(const std::string& failedNodeId, const std::string& healthyNodeId);

private:
    FailoverManager() = default;
    std::map<std::string, bool> m_nodeStatus;
    std::mutex m_mutex;
};

} // namespace cluster
} // namespace nanoai

#endif // NANOAI_FAILOVER_MANAGER_H
