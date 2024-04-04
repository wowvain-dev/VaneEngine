#pragma once

#include <Core/Memory/MemUtil.hpp>
#include <Core/Defines.hpp>

namespace Vane::Memory {
class StackAllocator {
public:
    using Marker = u_size;

    StackAllocator() = delete;
    explicit StackAllocator(u_size stackSize);
    ~StackAllocator();

    /// @brief Grab properly aligned memory from the stack allocator. You
    /// probably want to `getMarker()` before calling this if you want to
    /// that marker.
    ///
    /// @param size Number of bytes you want, in bytes
    /// @param alignment Alignment requirement of the memory, must be power of 2
    /// and less than 128
    /// @return Pointer to allocated memory
    void* alloc(u_size size, u8 alignment);

    /// @brief Create a new object on the stack allocator. The constructor is
    /// automatically called. The memory is 16 aligned by default. If you are 
    /// using this, you probably need to call the destructor on your own.
    ///
    /// @tparam T type of object you want to create
    /// @tparam args Arguments for the constructor
    /// @return Pointer to new object
    template <typename T, typename... args>
    T* New(args...);

    template <typename T>
    T* NewArr(u_size length, u8 alignment);

    /// @brief Free the stack allocator to a specific marker.
    /// @param marker Marker to free to
    void freeToMarker(const Marker marker) { top = marker; }

    /// @brief Clear the whole stack allocator to its bottom. All memory 
    /// will be available for new allocations again
    void clear() { top = 0; };

    /// @brief Get the current marker position
    /// @return
    Marker getMarker() const { return top; }

private:
    Marker top;
    u_size totalSize;
    void* bottom;
    u_ptr bottomAddress;
};

template <typename T, typename... args>
T* StackAllocator::New(args... argList) {
    void* mem = alloc(sizeof(T), MemUtil::ALIGNMENT);
    return new(mem) T(argList...);
}

template <typename T>
T* StackAllocator::NewArr(u_size length, const u8 alignment) {
    void* mem = alloc(sizeof(T) * length, alignment);
    char* allocAddress = static_cast<char*>(mem);

    for (int i = 0; i < length; i++) new(allocAddress + i * sizeof(T)) T;

    return static_cast<T*>(mem);
}
};
