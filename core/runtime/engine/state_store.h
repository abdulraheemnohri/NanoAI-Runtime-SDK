#ifndef NANOAI_STATE_STORE_H
#define NANOAI_STATE_STORE_H

#include <string>
#include <map>
#include <mutex>

namespace nanoai {
namespace engine {

class StateStore {
public:
    static StateStore& getInstance();

    void saveSessionState(const std::string& sessionId, const std::string& data);
    std::string getSessionState(const std::string& sessionId);
    void clearSession(const std::string& sessionId);

private:
    StateStore() = default;
    std::map<std::string, std::string> m_states;
    std::mutex m_mutex;
};

} // namespace engine
} // namespace nanoai

#endif // NANOAI_STATE_STORE_H
