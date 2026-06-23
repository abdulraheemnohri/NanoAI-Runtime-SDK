#ifndef NANOAI_OS_SERVICE_H
#define NANOAI_OS_SERVICE_H

#include <string>
#include <vector>

namespace nanoai {

class AiOSService {
public:
    static bool startService();
    static bool stopService();
    static void broadcastMessage(const std::string& message);
    static bool isServiceRunning();
};

} // namespace nanoai

#endif // NANOAI_OS_SERVICE_H
