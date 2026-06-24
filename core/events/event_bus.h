#ifndef NANOAI_EVENT_BUS_H
#define NANOAI_EVENT_BUS_H

#include <string>
#include <vector>
#include <functional>
#include <mutex>
#include <map>

namespace nanoai {
namespace events {

enum class SystemEvent {
    MODEL_LOADED,
    TASK_STARTED,
    TASK_COMPLETED,
    CLUSTER_NODE_JOINED,
    HARDWARE_ALERT,
    SECURITY_VIOLATION
};

using EventCallback = std::function<void(const std::string& payload)>;

class EventBus {
public:
    static EventBus& getInstance();

    void subscribe(SystemEvent type, EventCallback callback);
    void publish(SystemEvent type, const std::string& payload);

private:
    EventBus() = default;
    std::map<SystemEvent, std::vector<EventCallback>> m_subscribers;
    std::mutex m_mutex;
};

} // namespace events
} // namespace nanoai

#endif // NANOAI_EVENT_BUS_H
