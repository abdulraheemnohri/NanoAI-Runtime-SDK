#include "logger.h"
#include <iostream>
#include <chrono>

namespace nanoai {
namespace logging {

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(LogLevel level, const std::string& module, const std::string& message) {
    std::lock_guard<std::mutex> lock(m_mutex);

    std::string lvlStr;
    switch(level) {
        case LogLevel::INFO: lvlStr = "INFO"; break;
        case LogLevel::WARNING: lvlStr = "WARN"; break;
        case LogLevel::ERROR: lvlStr = "ERR "; break;
        case LogLevel::CRITICAL: lvlStr = "CRIT"; break;
    }

    std::cout << "[" << lvlStr << "][" << module << "] " << message << std::endl;
}

} // namespace logging
} // namespace nanoai
