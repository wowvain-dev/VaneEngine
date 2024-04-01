#pragma once

#include <map>

#include "../Asserts.hpp"
#include "../Defines.hpp"

namespace Vane::Memory {

template <typename T>
class ObjectHandle;
    
class MemoryArena {
private:
    MemoryArena() = delete;

    /// @brief Create a new memory arena of specified size
    /// @param size Size in bytes
    explicit MemoryArena(const u_size size);
    ~MemoryArena();

    /// @brief Create a new object on this memory arena. You need
    /// to manually call `DeleteDynamic` to free the memory of this object.
    /// The dynamic memory area will be automatically defragmented so it's not a good
    /// idea to create super big objects with this function.
    /// @tparam T type of the object you want to create
    /// @return
    template <typename T, typename ...args>
    ObjectHandle<T> newDynamic(args...);

    /// @brief Delete an object that was created with `newDynamic`. The memory will be freed
    /// and the constructor will be automatically called on the object
    ///
    /// @tparam T
    /// @param objToDelete Object you want to delete
    template <typename T>
    void deleteDynamic(const ObjectHandle<T>& objToDelete);

    /// @brief Helper function for allocate memory with MemoryArena
    /// @param size Size in byte
    /// @param outSize Returns the actual used size of memory (extra is possible
    /// because of alignment requirement)
    /// @return Pointer to memory
    void* alloc(const u_size size, u_size& outSize);

    /// @brief Defragment the memory arena. This should be called by the memory manager
    void defragment();

    /// @brief A helper function used to move a memory chunk to the left, eliminate free
    /// space between it and the object immediately to its left
    /// @param index Index of the entry to move
    void moveLeft(u32 index);

    /// Only for internal debugging
    void print() const;

    /// Only for internal use
    u_ptr getUsedSize() const;

    static const u32 maxHandleCount = 2048;
    static inline u32 nextUniqueID = 0;
    static class HandleEntry entryArr[];

    std::map<u_ptr, int> addressIndexMap;
    u32 curIndex = 0;
    u_ptr leftAddress{};
    u_ptr rightAddress{};
    void* memHead{};

    template <typename T>
    friend class ObjectHandle;
    friend class MemoryManager;
};

    template <typename T, typename... args>
    ObjectHandle<T> MemoryArena::newDynamic(args... arglist) {
        /// TODO(wowvain-dev): revise later
        u_size size;
        void* mem = alloc(sizeof(T), size);
        ObjectHandle<T> handle = ObjectHandle<T>{mem, nextUniqueID++, size, arglist...};
        addressIndexMap.emplace(handle.getObjAddress(), handle.index);

        return handle;
    }

    template <typename T>
    void MemoryArena::deleteDynamic(const ObjectHandle<T>& objToDelete) {
        auto addressIndexPair = addressIndexMap.find(objToDelete.getObjAddress());

        if (addressIndexPair != addressIndexMap.end()) {
            addressIndexMap.erase(addressIndexPair);
            objToDelete.eraseObject();
        } else {
            throw std::exception(
                "MemoryArena::deleteDynamic -> Double deleting handle!");
        }
    }


};

