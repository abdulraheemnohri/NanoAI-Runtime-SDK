#ifndef NANOAI_MODEL_METADATA_H
#define NANOAI_MODEL_METADATA_H

#include <string>
#include <vector>
#include <map>

namespace nanoai {
namespace models {

struct ModelMetadata {
    std::string modelId;
    std::string name;
    std::string version;
    std::string author;
    std::string architecture;
    std::vector<std::string> capabilities;
    std::map<std::string, std::string> parameters;
};

class MetadataParser {
public:
    static ModelMetadata parse(const std::string& path);
};

} // namespace models
} // namespace nanoai

#endif // NANOAI_MODEL_METADATA_H
