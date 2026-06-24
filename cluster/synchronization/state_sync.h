#ifndef NANOAI_STATE_SYNC_H
#define NANOAI_STATE_SYNC_H

#include <string>
#include <vector>

namespace nanoai {
namespace cluster {

class StateSync {
public:
    static StateSync& getInstance();

    void syncGlobalState();
    void broadcastStateUpdate(const std::string& key, const std::string& value);
};

} // namespace cluster
} // namespace nanoai

#endif // NANOAI_STATE_SYNC_H
