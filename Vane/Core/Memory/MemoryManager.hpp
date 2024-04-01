#pragma once

#include "MemUtil.h"
#include "../Defines.hpp"
#include "../Asserts.hpp"
#include "../Logger.hpp"

namespace Vane::Memory {

class VAPI MemoryManager {
public:
    /// @brief Contains the configuration of sizes for the allocators.
    struct MemoryConfig {
        v_size levelAllocatorSize = 10_MB;
        v_size singleFrameAllocatorSize = 10_MB;
        v_size doubleBufferedAllocatorSize = 10_MB;
        v_size dynamicArenaSize = 10_MB;
        v_size freeListAllocatorSize = 10_MB;
        v_size freeListIncrement = 10_MB;
        v_size defaultPoolIncrement = 50;
        v_size entityPoolInitialSize = 100;
        v_size entityPoolIncrement = 50;
    };

    /// @brief Grab some properly aligned free memory, will be freed at the end of frame.
    /// @param size Size in bytes
    /// @param alignment Alignment requirement of property, power of 2, less than 128.
    static void* allocOnSingleFrame(v_size size, u8 alignment = MemUtil::ALIGNMENT);


    /// @brief Create a new object whose memory will be cleared at the end of the frame. You need to
    /// manually call destructor on that object.
    template <typename T, typename... Args>
    static T* newOnSingleFrame(Args&&...);

    template <typename T>
    static T* newArrOnSingleFrame(v_size length, u8 alignment = MemUtil::ALIGNMENT);

    /// @brief Grab some properly aligned free memory to use. The memory will be freed at the end of next frame.
    /// @param size Size in byte
    /// @param alignment Alignment requirement of property, must be power of 2 and less than 256.
    static void* allocOnDoubleBuffered(v_size size, u8 alignment = MemUtil::ALIGNMENT);

    /// @brief Create a new object whose memory is going to be cleared at the end of next frame. You need to
    /// manually call destructor on that object.
    /// @tparam T type of object to create \return
    template <typename T, typename... Args>
    static T* newOnDoubleBuffered(Args&&...);

    template <typename T>
    static T* newArrOnDoubleBuffered(v_size length, u8 alignment = MemUtil::ALIGNMENT);

    /// ?
    static void* allocOnStack(v_size size, u8 alignment = MemUtil::ALIGNMENT);

    template <typename T, typename... Args>
    static T* newOnStack(Args&&...);

    template <typename T>
    static T* newArrOnStack(v_size length, u8 alignment = MemUtil::ALIGNMENT);
};
    
}
