#pragma once

#include "../Defines.hpp"
#include "../Asserts.hpp"
#include "../Logger.hpp"

#include "MemUtil.hpp"
#include "MemoryArena.hpp"
#include "ObjectHandle.hpp"

namespace Vane::Memory {

class  MemoryManager {
public:
    /// @brief Contains the configuration of sizes for the allocators.
    struct MemoryConfig {
        u_size levelAllocatorSize = 10_MB;
        u_size singleFrameAllocatorSize = 10_MB;
        u_size doubleBufferedAllocatorSize = 10_MB;
        u_size dynamicArenaSize = 10_MB;
        u_size freeListAllocatorSize = 10_MB;
        u_size freeListIncrement = 10_MB;
        u_size defaultPoolIncrement = 50;
        u_size entityPoolInitialSize = 100;
        u_size entityPoolIncrement = 50;
    };

    /// @brief Grab some properly aligned free memory, will be freed at the end of frame.
    /// @param size Size in bytes
    /// @param alignment Alignment requirement of property, power of 2, less than 128.
    static void* allocOnSingleFrame(u_size size, u8 alignment = MemUtil::ALIGNMENT);


    /// @brief Create a new object whose memory will be cleared at the end of the frame. You need to
    /// manually call destructor on that object.
    template <typename T, typename... Args>
    static T* newOnSingleFrame(Args&&...);

    template <typename T>
    static T* newArrOnSingleFrame(u_size length, u8 alignment = MemUtil::ALIGNMENT);

    /// @brief Grab some properly aligned free memory to use. The memory will be freed at the end of next frame.
    /// @param size Size in byte
    /// @param alignment Alignment requirement of property, must be power of 2 and less than 256.
    static void* allocOnDoubleBuffered(u_size size, u8 alignment = MemUtil::ALIGNMENT);

    /// @brief Create a new object whose memory is going to be cleared at the end of next frame. You need to
    /// manually call destructor on that object.
    /// @tparam T type of object to create \return
    template <typename T, typename... Args>
    static T* newOnDoubleBuffered(Args&&...);

    template <typename T>
    static T* newArrOnDoubleBuffered(u_size length, u8 alignment = MemUtil::ALIGNMENT);

    /// ?
    static void* allocOnStack(u_size size, u8 alignment = MemUtil::ALIGNMENT);

    template <typename T, typename... Args>
    static T* newOnStack(Args&&...);

    template <typename T>
    static T* newArrOnStack(u_size length, u8 alignment = MemUtil::ALIGNMENT);

    static void* allocOnFreeList(u_size size, u8 alignment = MemUtil::ALIGNMENT);
    static void* reallocOnFreeList(void* memPtr, u_size newSize, u8 alignment = MemUtil::ALIGNMENT);
    static void  freeOnFreeList(void* memPtr);

    template <typename T, typename... Args>
    static T* newOnFreeList(Args&&... argList);
    template <typename T>
    static void deleteOnFreeList(T* ptrToDelete);

    template <typename T>
    static T* newArrOnFreeList(u_size length, u8 alignment = MemUtil::ALIGNMENT);
    template <typename T>
    static void deleteArrOnFreeList(u_size length, T* ptrToDelete);

    ///@brief Create an object that will sit on the dynamic memory area. You need to manually
    ///call `DeleteDynamic` to free the memory of this object. The dynamic memory area
    ///will be automatically defragmented so it's not a good idea to create super big
    ///objects with this function.
    // template <typename T, typename... Args>
    // static 
    
};
    
}
