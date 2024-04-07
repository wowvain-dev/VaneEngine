#include "CVar.hpp"

#include <unordered_map>

#include <Vane/Config/CVarRegistry.hpp>

namespace Vane {
template class CVar<float>;

std::unordered_map<StringId, ICVar*> CVarRegistry::registry;
std::vector<std::string_view> CVarRegistry::keys;

CVarString::CVarString(
    const std::string& name,
    const std::string_view defaultValue
) : ICVar(name), sVal{defaultValue} {
    CVarRegistry::RegisterVariable(this);  
}

CVarString::CVarString(const std::string_view name) : ICVar(name) {
    CVarRegistry::RegisterVariable(this);
}
};