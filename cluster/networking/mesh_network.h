#ifndef NANOAI_MESH_NETWORK_H
#define NANOAI_MESH_NETWORK_H

#include <string>
#include <vector>
#include <mutex>

namespace nanoai {
namespace cluster {

struct PeerInfo {
    std::string peerId;
    std::string role; // AGENT, WORKER, STORAGE
    float trustScore;
};

class MeshNetwork {
public:
    static MeshNetwork& getInstance();
    void joinSwarm(const std::string& swarmId);
    void broadcastEvent(const std::string& eventType, const std::string& payload);
    std::vector<PeerInfo> getConnectedPeers();

    void removePeer(const std::string& peerId);

private:
    MeshNetwork() = default;
    std::vector<PeerInfo> m_peers;
    std::mutex m_mutex;
};

} // namespace cluster
} // namespace nanoai

#endif // NANOAI_MESH_NETWORK_H
