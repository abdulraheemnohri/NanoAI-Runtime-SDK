#ifndef NANOAI_MODEL_VALIDATOR_H
#define NANOAI_MODEL_VALIDATOR_H

#include <string>
#include <vector>

namespace nanoai {
namespace models {

struct ValidationResult {
    bool isValid;
    std::string error;
    std::vector<std::string> warnings;
};

class ModelValidator {
public:
    static ValidationResult validate(const std::string& path);
};

} // namespace models
} // namespace nanoai

#endif // NANOAI_MODEL_VALIDATOR_H
