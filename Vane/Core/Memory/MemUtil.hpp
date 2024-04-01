#pragma once

#include "../Asserts.hpp"
#include "../Defines.hpp"

#include <string>

namespace Vane::Memory {
    /// @brief Memory allocator class with utilities that are intended
    /// only for internal use.
class MemUtil {
public:
    static const u8 ALIGNMENT = 16;
    static void CheckAlignment(u8 alignment);

    /// @brief Allocate properly aligned memory. The adjusted size
    /// of memory is stored as head (1 byte to the left of the
    /// returned raw memory pointer)
    ///
    /// @param size Size in bytes
    /// @param alignment Alignment requirement . Must be power of 2
    /// and less than 128 and greater than or equal to 8.
    /// @return A raw pointer to the newly allocated memory address
    static void* alloc(u_size size, u8 alignment = ALIGNMENT);

    /// @brief Free the properly aligned memory address
    static void free(void*);

    /// @brief Util function to get name for type. 
    template <typename T>
    static std::string getNameForType() {
        std::string name = typeid(T).name();
        auto pos = name.find("::");

        if (pos != std::string::npos) {
            name = name.substr(pos+2);
        }

        pos = name.find(" * __ptr64");
        if (pos != std::string::npos) {
            name = name.substr(0, pos);
            name += "*";
        }

        return name;
    }
};
}

