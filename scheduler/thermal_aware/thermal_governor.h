#ifndef NANOAI_THERMAL_GOVERNOR_H
#define NANOAI_THERMAL_GOVERNOR_H

namespace nanoai {
namespace scheduler {

class ThermalGovernor {
public:
    static float getThrottlingFactor() {
        // Simulated: 1.0 = full speed, 0.5 = throttled
        return 0.95f;
    }
};

} }
#endif
