#ifndef NANOAI_METAL_BACKEND_H
#define NANOAI_METAL_BACKEND_H

#include <string>
#include <iostream>

namespace nanoai {
namespace backends {

class MetalBackend {
public:
    static bool isAvailable() {
#ifdef __APPLE__
        return true;
#else
        return false;
#endif
    }

    void initialize() {
        std::cout << "Metal: Initializing Apple Silicon GPU Backend..." << std::endl;
    }

    std::string getDeviceInfo() {
        return "Apple M-series GPU (Simulated)";
    }
};

} // namespace backends
} // namespace nanoai

#endif // NANOAI_METAL_BACKEND_H
