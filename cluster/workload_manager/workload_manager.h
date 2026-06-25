#ifndef NANOAI_WORKLOAD_MANAGER_H
#define NANOAI_WORKLOAD_MANAGER_H

#include <string>
#include <vector>
#include <mutex>

namespace nanoai {
namespace cluster {

struct WorkloadChunk {
    std::string chunkId;
    std::string data;
    int sequenceNumber;
};

class WorkloadManager {
public:
    static WorkloadManager& getInstance();

    std::vector<WorkloadChunk> splitWorkload(const std::string& input, int chunkCount);
    void distributeWorkload(const std::vector<WorkloadChunk>& chunks, const std::vector<std::string>& nodeIds);
    std::string assembleWorkload(const std::vector<WorkloadChunk>& chunks);

private:
    WorkloadManager() = default;
    std::mutex m_mutex;
};

} // namespace cluster
} // namespace nanoai

#endif // NANOAI_WORKLOAD_MANAGER_H
