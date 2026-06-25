#ifndef NANOAI_THERMAL_GOVERNOR_H
#define NANOAI_THERMAL_GOVERNOR_H

namespace nanoai {
namespace scheduler {

class ThermalGovernor {
public:
    static ThermalGovernor& getInstance();

    float getThrottlingFactor();
    float getCurrentTemperature();
    bool isOverheating();

private:
    ThermalGovernor() = default;
};

} // namespace scheduler
} // namespace nanoai

#endif // NANOAI_THERMAL_GOVERNOR_H
