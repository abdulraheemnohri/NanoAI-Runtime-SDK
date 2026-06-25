#ifndef NANOAI_STREAM_SERVER_H
#define NANOAI_STREAM_SERVER_H

#include <string>
#include <vector>
#include <mutex>

namespace nanoai {
namespace dashboard {

class StreamServer {
public:
    static StreamServer& getInstance();

    void start(int port);
    void stop();
    void pushTelemetry(const std::string& json);
    void broadcastEvent(const std::string& type, const std::string& payload);

private:
    StreamServer() = default;
    bool m_active;
    std::mutex m_mutex;
};

} // namespace dashboard
} // namespace nanoai

#endif // NANOAI_STREAM_SERVER_H
