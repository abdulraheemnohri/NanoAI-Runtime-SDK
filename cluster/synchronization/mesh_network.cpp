#include "mesh_network.h"
#include "../discovery/discovery_service.h"
#include <iostream>

namespace nanoai {
namespace cluster {

MeshNetwork& MeshNetwork::getInstance() {
    static MeshNetwork instance;
    return instance;
}

void MeshNetwork::joinSwarm(const std::string& swarmId) {
    std::cout << "MeshNetwork: Joining P2P AI Swarm [" << swarmId << "]" << std::endl;

    // Automatically bridge discovery nodes to peers
    DiscoveryService::getInstance().onNodeFound([this](RemoteNodeInfo node) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_peers.push_back({node.id, "WORKER", 1.0f - node.currentLoad});
        std::cout << "MeshNetwork: Peer " << node.id << " synchronized from discovery." << std::endl;
    });
}

void MeshNetwork::broadcastEvent(const std::string& type, const std::string& payload) {
    std::cout << "MeshNetwork: Broadcasting " << type << " to swarm..." << std::endl;
}

std::vector<PeerInfo> MeshNetwork::getConnectedPeers() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_peers;
}

} // namespace cluster
} // namespace nanoai
