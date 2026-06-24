#ifndef NANOAI_MODEL_METADATA_H
#define NANOAI_MODEL_METADATA_H
#include <string>
#include <vector>
namespace nanoai { namespace models {
struct ModelMetadata {
    std::string name;
    std::string version;
    std::string author;
    std::vector<std::string> capabilities;
};
} }
#endif
