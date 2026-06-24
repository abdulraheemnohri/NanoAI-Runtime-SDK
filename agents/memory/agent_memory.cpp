#include "agent_memory.h"

namespace nanoai {
namespace agents {

AgentMemory& AgentMemory::getInstance() {
    static AgentMemory instance;
    return instance;
}

void AgentMemory::remember(const std::string& key, const std::string& value) {
    m_mem[key] = value;
}

std::string AgentMemory::recall(const std::string& key) {
    if (m_mem.count(key)) return m_mem.at(key);
    return "";
}

} }
