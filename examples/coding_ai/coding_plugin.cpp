#include "../../core/plugins/plugin_manager.h"
#include <iostream>

namespace nanoai {
namespace plugins {

class CodingAiPlugin : public AiPlugin {
public:
    std::string getPluginId() const override { return "CodeRefactor_Pro"; }
    void initialize() override {
        std::cout << "CodingPlugin: Initializing Linter/Refactor engine..." << std::endl;
    }
};

} }
