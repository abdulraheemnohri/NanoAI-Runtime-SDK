#include "../../core/plugins/plugin_manager.h"
#include <iostream>

namespace nanoai {
namespace plugins {

class MedicalAiPlugin : public AiPlugin {
public:
    std::string getPluginId() const override { return "MedicalDiagnostics_v1"; }
    void initialize() override {
        std::cout << "MedicalPlugin: Loading anatomy datasets..." << std::endl;
    }
};

} }
