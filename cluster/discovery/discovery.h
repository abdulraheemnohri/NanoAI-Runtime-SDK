#ifndef NANOAI_DISCOVERY_SERVICE_H
#define NANOAI_DISCOVERY_SERVICE_H

#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>

namespace nanoai {
namespace cluster {

struct RemoteNodeInfo {
    std::string id;
    std::string ip;
    std::string hardware;
    float currentLoad;
};

class DiscoveryService {
public:
    static DiscoveryService& getInstance();
    void startDiscovery();
    void stopDiscovery();

    std::vector<RemoteNodeInfo> getDiscoveredNodes();
    void onNodeFound(std::function<void(RemoteNodeInfo)> callback);

    ~DiscoveryService();

private:
    DiscoveryService();
    void discoveryLoop();

    std::vector<RemoteNodeInfo> m_nodes;
    std::mutex m_mutex;
    bool m_running;
    std::thread m_thread;
    std::function<void(RemoteNodeInfo)> m_callback;
};

} // namespace cluster
} // namespace nanoai

#endif // NANOAI_DISCOVERY_SERVICE_H
