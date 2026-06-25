#include "stream_server.h"
#include <iostream>

namespace nanoai {
namespace dashboard {

StreamServer& StreamServer::getInstance() {
    static StreamServer instance;
    return instance;
}

void StreamServer::start(int port) {
    std::cout << "StreamServer: Starting real-time WebSocket server on port " << port << "..." << std::endl;
    m_active = true;
}

void StreamServer::stop() {
    std::cout << "StreamServer: Shutting down telemetry stream." << std::endl;
    m_active = false;
}

void StreamServer::pushTelemetry(const std::string& json) {
    if (m_active) {
        // Simulated: Logic to push to connected clients
    }
}

void StreamServer::broadcastEvent(const std::string& type, const std::string& payload) {
    if (m_active) {
        std::cout << "StreamServer: [Broadcast] " << type << " -> Swarm Hub." << std::endl;
    }
}

} // namespace dashboard
} // namespace nanoai
