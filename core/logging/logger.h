#ifndef NANOAI_LOGGER_H
#define NANOAI_LOGGER_H

#include <string>
#include <mutex>

namespace nanoai {
namespace logging {

enum class LogLevel { INFO, WARNING, ERROR, CRITICAL };

class Logger {
public:
    static Logger& getInstance();
    void log(LogLevel level, const std::string& module, const std::string& message);

private:
    Logger() = default;
    std::mutex m_mutex;
};

} // namespace logging
} // namespace nanoai

#endif // NANOAI_LOGGER_H
