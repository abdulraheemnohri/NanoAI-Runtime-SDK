#ifndef NANOAI_AGENT_MEMORY_H
#define NANOAI_AGENT_MEMORY_H

#include <string>
#include <map>

namespace nanoai {
namespace agents {

class AgentMemory {
public:
    static AgentMemory& getInstance();
    void remember(const std::string& key, const std::string& value);
    std::string recall(const std::string& key);

private:
    AgentMemory() = default;
    std::map<std::string, std::string> m_mem;
};

} }
#endif
