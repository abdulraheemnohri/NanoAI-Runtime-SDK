#include "event_bus.h"

namespace nanoai {
namespace events {

EventBus& EventBus::getInstance() {
    static EventBus instance;
    return instance;
}

void EventBus::subscribe(SystemEvent type, EventCallback callback) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_subscribers[type].push_back(callback);
}

void EventBus::publish(SystemEvent type, const std::string& payload) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_subscribers.count(type)) {
        for (auto& cb : m_subscribers[type]) {
            cb(payload);
        }
    }
}

} // namespace events
} // namespace nanoai
