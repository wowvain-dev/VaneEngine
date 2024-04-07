#pragma once

#include <string>
#include <unordered_map>

#include <Vane/Utils/sid.hpp>
#include <Vane/Core/Logger.hpp>
#include <Vane/Core/Defines.hpp>

using std::string;
using std::string_view;

namespace Vane {
/**
 * @brief Base class of console variables
 */
class ICVar {
public:
    const string name;
    const StringId nameID;

    /**
     * @brief Set the Val object, abstract
     *
     * @param strVal convert from this string
     */
    virtual void SetVal(const string_view strVal) = 0;

protected:
    /**
     * @brief Construct a new `ICVar` object, cannot publicly create `ICVar`
     *
     * @param name
     */
    explicit ICVar(string_view name) :
        name{name}, nameID{SID(name.data())} {}

    /**
     * @brief Destroy the ICVar object, cannot instance ICVar
     */
    virtual ~ICVar() {}


};
}
