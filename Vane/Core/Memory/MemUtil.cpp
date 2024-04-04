#include "MemUtil.hpp"

#include <stdexcept>

#include <Core/Asserts.hpp>

using namespace Vane::Memory;

void MemUtil::CheckAlignment(u8 alignment) {
    const bool isValid = alignment >= 8 && alignment <= 128 &&
            (alignment & (alignment - 1)) == 0; // Power of 2

    if (!isValid) {
        throw std::invalid_argument{
            "MemoryAllocator::CheckAlignment -> Illegal Alignment: "
            "\t(alignment >= 8 && alignment <= 128 && (alignment & (alignment -1)) == 0)"
        };
    }
}


void* MemUtil::alloc(const u_size size, const u8 alignment) {
    CheckAlignment(alignment);

    // Total size with alignment
    const u_size expandedSize = size + alignment;
    // The raw address of the allocation
    const u_ptr rawAddress = reinterpret_cast<uintptr_t>(std::malloc(expandedSize));
    const u_ptr misAlignment = rawAddress & (alignment - 1);
    const u8 adjustment = alignment - static_cast<u8>(misAlignment);
    const u_ptr alignedAddress = rawAddress + adjustment;
    auto alignedMemory = reinterpret_cast<u8*>(alignedAddress);

    alignedMemory[-1] = adjustment;

    VASSERT_MSG(reinterpret_cast<u_ptr>(alignedMemory) % alignment == 0,
                "Bad alignment"
    )

    return static_cast<void*>(alignedMemory);
}

void MemUtil::free(void* memoryPtr) {
    const u8* alignedMemory = reinterpret_cast<u8*>(memoryPtr);
    const u_ptr_diff adjustment = static_cast<u_ptr_diff>(alignedMemory[-1]);
    const u_ptr alignedAddress = reinterpret_cast<u_ptr>(memoryPtr);
    const u_ptr rawAddress = alignedAddress - adjustment;

    void* rawMem = reinterpret_cast<void*>(rawAddress);

    std::free(rawMem);
}
