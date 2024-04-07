#pragma once

#include <Vane/Core/Defines.hpp>
#include <Vane/Core/Asserts.hpp>
#include <Vane/Core/Logger.hpp>

#include <Vane/Core/Memory/DoubleBufferedAllocator.hpp>
#include <Vane/Core/Memory/FreeListAllocator.hpp>
#include <Vane/Core/Memory/MemUtil.hpp>
#include <Vane/Core/Memory/MemoryArena.hpp>
#include <Vane/Core/Memory/ObjectHandle.hpp>
#include <Vane/Core/Memory/StackAllocator.hpp>

namespace Vane::Memory {
class MemoryManager {
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
    static void *allocOnSingleFrame(u_size size, u8 alignment = MemUtil::ALIGNMENT);


    /// @brief Create a new object whose memory will be cleared at the end of the frame. You need to
    /// manually call destructor on that object.
    template <typename T, typename... Args>
    static T *newOnSingleFrame(Args &&...);

    template <typename T>
    static T *newArrOnSingleFrame(u_size length, u8 alignment = MemUtil::ALIGNMENT);

    /// @brief Grab some properly aligned free memory to use. The memory will be freed at the end of next frame.
    /// @param size Size in byte
    /// @param alignment Alignment requirement of property, must be power of 2 and less than 256.
    static void *allocOnDoubleBuffered(u_size size, u8 alignment = MemUtil::ALIGNMENT);

    /// @brief Create a new object whose memory is going to be cleared at the end of next frame. You need to
    /// manually call destructor on that object.
    /// @tparam T type of object to create \return
    template <typename T, typename... Args>
    static T *newOnDoubleBuffered(Args &&...);

    template <typename T>
    static T *newArrOnDoubleBuffered(u_size length, u8 alignment = MemUtil::ALIGNMENT);

    /// ?
    static void *allocOnStack(u_size size, u8 alignment = MemUtil::ALIGNMENT);

    template <typename T, typename... Args>
    static T *newOnStack(Args &&...);

    template <typename T>
    static T *newArrOnStack(u_size length, u8 alignment = MemUtil::ALIGNMENT);

    static void *allocOnFreeList(u_size size, u8 alignment = MemUtil::ALIGNMENT);
    static void *reallocOnFreeList(void *memPtr, u_size newSize, u8 alignment = MemUtil::ALIGNMENT);
    static void freeOnFreeList(void *memPtr);

    template <typename T, typename... Args>
    static T *newOnFreeList(Args &&... argList);
    template <typename T>
    static void deleteOnFreeList(T *ptrToDelete);

    template <typename T>
    static T *newArrOnFreeList(u_size length, u8 alignment = MemUtil::ALIGNMENT);
    template <typename T>
    static void deleteArrOnFreeList(u_size length, T *ptrToDelete);

    /// @brief Create an object that will sit on the dynamic memory area. You need to manually
    /// call `DeleteDynamic` to free the memory of this object. The dynamic memory area
    /// will be automatically defragmented so it's not a good idea to create super big
    /// objects with this function.
    /// @tparam T Type of the object you want to create
    /// @return
    template <typename T, typename... Args>
    static ObjectHandle<T> newDynamic(Args &&...);

    /// @brief Delete an object that was created with `newDynamic`. The memory will
    /// be freed and the constructor will be automatically called on the object
    ///
    /// @tparam T
    /// @param objToDelete Object you want to delete
    template <typename T>
    static void DeleteDynamic(const ObjectHandle<T> &objToDelete);

private:
    /// @brief Start up the memory manager. This creates the single frame
    /// allocator, the double buffered allocator, and the dynamic arena. Their
    /// specific sizes can be specified in the config.
    MemoryManager();

    /// @brief Free all memory, any further attempt to use objects managed by
    /// the memory manager will crash the game.
    ~MemoryManager() = default;

    /// @brief Update the memory manager. This needs to be called in simulation
    /// update, and takes care of clearing and swapping single frame + double
    /// buffered allocators and defragment the dynamic memory area
    void Update();

    // Set the marker to clear when finishing a level
    // TODO(wowvain) ??
    void FinishEngineStartupListener();
    void ClearLevelMemory();

    static MemoryManager *getInstance();
    /// Internal test
    static void defragmentTest();

    static MemoryManager *s_Instance;

    /// ALLOCATORS
    u_size lvlMemStartMarker{};
    MemoryArena dynamicArena;
    StackAllocator levelAllocator;
    StackAllocator singleFrameAllocator;
    DoubleBufferedAllocator doubleBufferedAllocator;
    FreeListAllocator freeListAllocator;
};

// template <typename T, typename... Args>
// T* MemoryManager::newOnSingleFrame(Args&&... argList) {
//     
// }
}
