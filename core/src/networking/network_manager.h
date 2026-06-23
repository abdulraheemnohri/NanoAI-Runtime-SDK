#ifndef NANOAI_NETWORK_MANAGER_H
#define NANOAI_NETWORK_MANAGER_H

#include "nanoai/distributed.h"
#include <iostream>
#include <vector>

namespace nanoai {

class NetworkManager {
public:
    static bool initializeCluster(const std::string& clusterId);
    static std::vector<NodeInfo> discoverPeers();
    static bool offloadWorkload(const WorkloadChunk& chunk, const std::string& targetNodeId);
    static void handleIncomingWorkload();
};

} // namespace nanoai

#endif // NANOAI_NETWORK_MANAGER_H
