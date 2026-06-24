#include "thermal_governor.h"
#include <random>

namespace nanoai {
namespace scheduler {

ThermalGovernor& ThermalGovernor::getInstance() {
    static ThermalGovernor instance;
    return instance;
}

float ThermalGovernor::getCurrentTemperature() {
    return 40.0f + (rand() % 45); // Simulated degrees Celsius
}

bool ThermalGovernor::isOverheating() {
    return getCurrentTemperature() > 80.0f;
}

float ThermalGovernor::getThrottlingFactor() {
    float temp = getCurrentTemperature();
    if (temp > 85.0f) return 0.2f;
    if (temp > 75.0f) return 0.5f;
    if (temp > 65.0f) return 0.8f;
    return 1.0f;
}

} // namespace scheduler
} // namespace nanoai
