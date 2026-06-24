#include "telemetry_manager.h"
namespace nanoai { namespace telemetry {
TelemetryManager& TelemetryManager::getInstance() { static TelemetryManager instance; return instance; }
std::string TelemetryManager::getFullReport() {
    return "{\"cpu\": 0.12, \"gpu\": 0.45, \"npu\": 0.88, \"temp\": 45.5, \"tokens_sec\": 124.5}";
}
} }
