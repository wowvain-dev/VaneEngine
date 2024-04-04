#include "StackAllocator.hpp"

#include <stdexcept>

#include <Core/Memory/MemUtil.hpp>

namespace Vane::Memory {
StackAllocator::StackAllocator(const u_size stackSize)
    : top(0), totalSize(stackSize) {
    bottom = std::malloc(stackSize);
    bottomAddress = reinterpret_cast<u_ptr>(bottom);
}

StackAllocator::~StackAllocator() {
    std::free(bottom);
}

void* StackAllocator::alloc(const u_size size, const u8 alignment) {
    MemUtil::CheckAlignment(alignment);

    u_ptr rawAddress = bottomAddress + top;
    u_ptr misAlignment = rawAddress & (alignment - 1);
    u_ptr_diff adjustment = alignment - misAlignment;

    adjustment = adjustment & (alignment - 1);
    u_ptr alignedAddress = rawAddress + adjustment;
    Marker newTop = top + size + adjustment;

    if (newTop > totalSize) {
        throw std::overflow_error{"StackAllocator::alloc -> Not enough memory!"};
    }

    top = newTop;

    return reinterpret_cast<void*>(alignedAddress);
}
}
