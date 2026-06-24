#include "mesh_network.h"
#include "../discovery/discovery.h"
#include <iostream>
#include <algorithm>

namespace nanoai {
namespace cluster {

MeshNetwork& MeshNetwork::getInstance() {
    static MeshNetwork instance;
    return instance;
}

void MeshNetwork::joinSwarm(const std::string& swarmId) {
    std::cout << "MeshNetwork: Joining P2P AI Swarm [" << swarmId << "]" << std::endl;

    DiscoveryService::getInstance().onNodeFound([this](RemoteNodeInfo node) {
        std::lock_guard<std::mutex> lock(m_mutex);

        auto it = std::find_if(m_peers.begin(), m_peers.end(),
            [&node](const auto& p) { return p.peerId == node.id; });

        if (it == m_peers.end()) {
            m_peers.push_back({node.id, "WORKER", 1.0f - node.currentLoad});
            std::cout << "MeshNetwork: Peer " << node.id << " synchronized from discovery." << std::endl;
        }
    });
}

void MeshNetwork::broadcastEvent(const std::string& type, const std::string& payload) {
    std::cout << "MeshNetwork: Broadcasting " << type << " to swarm..." << std::endl;
}

std::vector<PeerInfo> MeshNetwork::getConnectedPeers() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_peers;
}

void MeshNetwork::removePeer(const std::string& peerId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_peers.erase(std::remove_if(m_peers.begin(), m_peers.end(),
        [&peerId](const auto& p) { return p.peerId == peerId; }), m_peers.end());
    std::cout << "MeshNetwork: Peer " << peerId << " disconnected." << std::endl;
}

} // namespace cluster
} // namespace nanoai
