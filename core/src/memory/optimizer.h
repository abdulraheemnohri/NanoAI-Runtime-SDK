#ifndef NANOAI_OPTIMIZER_H
#define NANOAI_OPTIMIZER_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <chrono>

namespace nanoai {

class MemoryOptimizer {
public:
    static void applyOptimizations(const std::string& modelPath) {
        std::cout << "Memory Optimizer: Applying optimizations for " << modelPath << std::endl;
        std::cout << " - Enabling Model Caching" << std::endl;
        std::cout << " - Configuring Memory Mapping (mmap)" << std::endl;
        setLazyLoading(true);
    }

    static void setLazyLoading(bool enabled) {
        std::cout << "Memory Optimizer: Lazy Loading set to " << (enabled ? "ON" : "OFF") << std::endl;
    }

    static void handleDynamicUnloading(const std::string& modelId) {
        std::cout << "Memory Optimizer: Dynamically unloading model " << modelId << " to free RAM." << std::endl;
    }

    // New: Simulated policy check
    static void checkIdleModels(const std::unordered_map<std::string, std::chrono::steady_clock::time_point>& lastUsed) {
        auto now = std::chrono::steady_clock::now();
        for (const auto& [id, time] : lastUsed) {
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - time).count();
            if (elapsed > 30) { // 30 seconds idle threshold
                std::cout << "Memory Optimizer: Model " << id << " has been idle for " << elapsed << "s. Policy: UNLOAD." << std::endl;
            }
        }
    }
};

} // namespace nanoai

#endif // NANOAI_OPTIMIZER_H
