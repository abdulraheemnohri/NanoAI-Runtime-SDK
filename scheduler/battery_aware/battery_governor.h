#ifndef NANOAI_BATTERY_GOVERNOR_H
#define NANOAI_BATTERY_GOVERNOR_H

namespace nanoai {
namespace scheduler {

enum class PowerMode { PERFORMANCE, BALANCED, POWER_SAVER };

class BatteryGovernor {
public:
    static BatteryGovernor& getInstance();

    int getBatteryLevel();
    PowerMode getOptimalPowerMode();
    bool shouldThrottlingForPower();

private:
    BatteryGovernor() = default;
};

} // namespace scheduler
} // namespace nanoai

#endif // NANOAI_BATTERY_GOVERNOR_H
