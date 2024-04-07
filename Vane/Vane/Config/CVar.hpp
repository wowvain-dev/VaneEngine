#pragma once

#include <string>
#include <sstream>

#include <Vane/Config/ICVar.hpp>

#include <Vane/Config/CVarRegistry.hpp>

namespace Vane {
/**
 * \brief Console Variable to be used by Config and console
 * \tparam T Template type must be have ostream operator>> and emptry constructor
 */
template <typename T>
class CVar : public ICVar {
public:
    /**
     * \brief Construct a new CVar object
     * \param name of the CVar to put into the map, referenced in configuration and console
     * \param defaultValue the value set by default (if not found in the config file)
     */
    CVar(const std::string &name, const T &defaultValue) :
        ICVar(name), value{defaultValue} { CVarRegistry::RegisterVariable(this); }

    /**
     * \brief Construct a new CVar object, default value set by default constructor of
     * templated parameter
     * \param name of the CVar to put into the map, referenced in configuration and console
     */
    explicit CVar(const std::string_view name) :
        ICVar(name), value{T()} { CVarRegistry::RegisterVariable(this); }

    /**
     * \brief Set the Val object 
     * \param strVal string value to be converted into value of type T
     */
    inline void SetVal(const std::string_view strVal) override {
        std::istringstream iss(strVal.data());
        iss >> value;
    }

    /**
     * \brief Get the Val object 
     * \return T the value set of the object
     */
    inline T GetVal() const { return value; }

private:
    T value;
};

class CVarString : public ICVar {
public:
    /**
     * \brief 
     * \param name of the CVar to put into the map, referenced in configuration and console
     * \param defaultValue the value set by default (if not found in the config file);
     */
    CVarString(const std::string& name, const std::string_view defaultValue);

    /**
     * \brief Construct a new CVar object, default value set by default constructor of string 
     * \param name of the CVar to put into the map, referenced in configuration and console
     */
    explicit CVarString(const std::string_view name);

    /**
     * \brief Set the Val object
     * \param strVal the string to set the value as
     */
    inline void SetVal(const std::string_view strVal) override { sVal = strVal; }

    inline std::string GetVal() const {
        return sVal;
    }

private:
    std::string sVal;
};
}
