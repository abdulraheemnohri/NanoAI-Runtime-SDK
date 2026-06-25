#ifndef NANOAI_BATTERY_GOVERNOR_H
#define NANOAI_BATTERY_GOVERNOR_H

#include <mutex>

namespace nanoai {
namespace scheduler {

enum class PowerMode { PERFORMANCE, BALANCED, POWER_SAVER, ECO_MODE };

class BatteryGovernor {
public:
    static BatteryGovernor& getInstance();

    int getBatteryLevel();
    PowerMode getOptimalPowerMode();
    bool shouldThrottlingForPower();

    void setEcoMode(bool enabled);
    bool isEcoModeEnabled() const;

private:
    BatteryGovernor();
    bool m_ecoMode;
    mutable std::mutex m_mutex;
};

} // namespace scheduler
} // namespace nanoai

#endif // NANOAI_BATTERY_GOVERNOR_H
