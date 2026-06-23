#ifndef NANOAI_DISTRIBUTED_H
#define NANOAI_DISTRIBUTED_H

#include <string>
#include <vector>
#include <cstdint>

namespace nanoai {

struct NodeInfo {
    std::string id;
    std::string address;
    float available_compute_power; // 0.0 to 1.0
    bool is_online;
};

struct WorkloadChunk {
    std::string task_id;
    int chunk_index;
    int total_chunks;
    std::vector<uint8_t> payload;
};

struct ClusterState {
    std::string cluster_id;
    std::vector<NodeInfo> nodes;
    bool is_master;
};

} // namespace nanoai

#endif // NANOAI_DISTRIBUTED_H
