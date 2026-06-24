#ifndef NANOAI_HEARTBEAT_H
#define NANOAI_HEARTBEAT_H

#include <string>

namespace nanoai {
namespace cluster {

class HeartbeatManager {
public:
    static HeartbeatManager& getInstance();
    void sendPing(const std::string& nodeId);
    bool checkNodeHealth(const std::string& nodeId);
};

} }
#endif
