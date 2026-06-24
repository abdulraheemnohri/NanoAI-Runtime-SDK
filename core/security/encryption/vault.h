#ifndef NANOAI_VAULT_H
#define NANOAI_VAULT_H

#include <string>

namespace nanoai {
namespace security {

class Vault {
public:
    static std::string encrypt(const std::string& data) { return "ENC:" + data; }
    static std::string decrypt(const std::string& data) { return data.substr(4); }
};

} }
#endif
