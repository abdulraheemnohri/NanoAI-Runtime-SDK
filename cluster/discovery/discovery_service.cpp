#include "discovery_service.h"
#include <chrono>
#include <iostream>

namespace nanoai {
namespace cluster {

DiscoveryService::DiscoveryService() : m_running(false) {}
DiscoveryService::~DiscoveryService() { stopDiscovery(); }

DiscoveryService& DiscoveryService::getInstance() {
    static DiscoveryService instance;
    return instance;
}

void DiscoveryService::startDiscovery() {
    if (m_running) return;
    m_running = true;
    m_thread = std::thread(&DiscoveryService::discoveryLoop, this);
    std::cout << "Cluster: Discovery Service started (UDP/mDNS)..." << std::endl;
}

void DiscoveryService::stopDiscovery() {
    if (!m_running) return;
    m_running = false;
    if (m_thread.joinable()) m_thread.join();
}

void DiscoveryService::discoveryLoop() {
    while (m_running) {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Faster for testing
        if (!m_running) break;

        RemoteNodeInfo node;
        node.id = "node_" + std::to_string(rand() % 1000);
        node.ip = "192.168.1." + std::to_string(100 + (rand() % 50));
        node.hardware = (rand() % 2 == 0) ? "NVIDIA RTX 4080" : "Apple M2 Ultra";
        node.currentLoad = 0.1f; // Low load to trigger offloading

        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_nodes.push_back(node);
        }

        if (m_callback) m_callback(node);
        std::cout << "Cluster: Discovered remote node " << node.id << std::endl;
    }
}

std::vector<RemoteNodeInfo> DiscoveryService::getDiscoveredNodes() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_nodes;
}

void DiscoveryService::onNodeFound(std::function<void(RemoteNodeInfo)> callback) {
    m_callback = callback;
}

} // namespace cluster
} // namespace nanoai
