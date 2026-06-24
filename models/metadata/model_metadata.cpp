#include "model_metadata.h"
#include <iostream>

namespace nanoai {
namespace models {

ModelMetadata MetadataParser::parse(const std::string& path) {
    std::cout << "Metadata: Parsing header for " << path << "..." << std::endl;

    ModelMetadata meta;
    meta.name = "Gemma-2b-IT";
    meta.version = "1.0.0";
    meta.author = "Google";
    meta.architecture = "Transformer";

    if (path.find("vision") != std::string::npos) {
        meta.capabilities = {"OCR", "DETECTION", "SEGMENTATION"};
    } else {
        meta.capabilities = {"TEXT_GEN", "SUMMARIZATION", "TRANSLATION"};
    }

    return meta;
}

} // namespace models
} // namespace nanoai
