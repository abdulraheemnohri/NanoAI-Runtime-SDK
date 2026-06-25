#include "battery_governor.h"
#include <random>
#include <iostream>

namespace nanoai {
namespace scheduler {

BatteryGovernor& BatteryGovernor::getInstance() {
    static BatteryGovernor instance;
    return instance;
}

BatteryGovernor::BatteryGovernor() : m_ecoMode(false) {}

int BatteryGovernor::getBatteryLevel() {
    return 5 + (rand() % 95);
}

PowerMode BatteryGovernor::getOptimalPowerMode() {
    if (isEcoModeEnabled()) return PowerMode::ECO_MODE;

    int level = getBatteryLevel();
    if (level < 15) return PowerMode::POWER_SAVER;
    if (level < 50) return PowerMode::BALANCED;
    return PowerMode::PERFORMANCE;
}

bool BatteryGovernor::shouldThrottlingForPower() {
    auto mode = getOptimalPowerMode();
    return mode == PowerMode::POWER_SAVER || mode == PowerMode::ECO_MODE;
}

void BatteryGovernor::setEcoMode(bool enabled) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_ecoMode = enabled;
    std::cout << "BatteryGovernor: Eco-Mode " << (enabled ? "ENABLED" : "DISABLED") << std::endl;
}

bool BatteryGovernor::isEcoModeEnabled() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_ecoMode;
}

} // namespace scheduler
} // namespace nanoai
