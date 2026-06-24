#include "battery_governor.h"
#include <random>

namespace nanoai {
namespace scheduler {

BatteryGovernor& BatteryGovernor::getInstance() {
    static BatteryGovernor instance;
    return instance;
}

int BatteryGovernor::getBatteryLevel() {
    return 5 + (rand() % 95); // Simulated battery percentage
}

PowerMode BatteryGovernor::getOptimalPowerMode() {
    int level = getBatteryLevel();
    if (level < 15) return PowerMode::POWER_SAVER;
    if (level < 50) return PowerMode::BALANCED;
    return PowerMode::PERFORMANCE;
}

bool BatteryGovernor::shouldThrottlingForPower() {
    return getOptimalPowerMode() == PowerMode::POWER_SAVER;
}

} // namespace scheduler
} // namespace nanoai
