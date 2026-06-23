#include "os_service.h"
#include <iostream>

namespace nanoai {

static bool g_service_active = false;

bool AiOSService::startService() {
    std::cout << "AI OS Layer: Starting universal background service..." << std::endl;
    g_service_active = true;
    return true;
}

bool AiOSService::stopService() {
    std::cout << "AI OS Layer: Stopping background service..." << std::endl;
    g_service_active = false;
    return true;
}

void AiOSService::broadcastMessage(const std::string& message) {
    if (g_service_active) {
        std::cout << "AI OS Layer: Broadcasting to system: " << message << std::endl;
    }
}

bool AiOSService::isServiceRunning() {
    return g_service_active;
}

} // namespace nanoai
