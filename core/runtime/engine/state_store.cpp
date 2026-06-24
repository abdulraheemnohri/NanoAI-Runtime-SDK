#include "state_store.h"

namespace nanoai {
namespace engine {

StateStore& StateStore::getInstance() {
    static StateStore instance;
    return instance;
}

void StateStore::saveSessionState(const std::string& sessionId, const std::string& data) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_states[sessionId] = data;
}

std::string StateStore::getSessionState(const std::string& sessionId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_states.count(sessionId)) return m_states.at(sessionId);
    return "";
}

void StateStore::clearSession(const std::string& sessionId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_states.erase(sessionId);
}

} // namespace engine
} // namespace nanoai
