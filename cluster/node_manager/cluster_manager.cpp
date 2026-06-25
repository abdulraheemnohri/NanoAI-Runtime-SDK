#include "cluster_manager.h"
#include "../discovery/discovery.h"
#include "../synchronization/state_sync.h"
#include <sstream>
#include <iostream>

namespace nanoai {
namespace cluster {

ClusterManager& ClusterManager::getInstance() {
    static ClusterManager instance;
    return instance;
}

std::string ClusterManager::getNodes() {
    auto nodes = DiscoveryService::getInstance().getDiscoveredNodes();
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < nodes.size(); ++i) {
        ss << "{\"id\": \"" << nodes[i].id << "\", \"ip\": \"" << nodes[i].ip
           << "\", \"hw\": \"" << nodes[i].hardware << "\", \"load\": " << nodes[i].currentLoad << "}";
        if (i < nodes.size() - 1) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

void ClusterManager::sync() {
    std::cout << "ClusterManager: Manual synchronization triggered." << std::endl;
    StateSync::getInstance().syncGlobalState();
}

} // namespace cluster
} // namespace nanoai
