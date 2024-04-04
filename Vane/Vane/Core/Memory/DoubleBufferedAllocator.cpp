#include "DoubleBufferedAllocator.hpp"

namespace Vane::Memory {
DoubleBufferedAllocator::DoubleBufferedAllocator(const u_size size)
    : stacks{StackAllocator{size}, StackAllocator{size}}, curStackIndex(0) {}

void* DoubleBufferedAllocator::alloc(const u_size size, const u8 alignment) {
    return stacks[curStackIndex].alloc(size, alignment);
}

void DoubleBufferedAllocator::swapBuffer() { curStackIndex = !curStackIndex; }

void DoubleBufferedAllocator::clearCurrentBuffer() {
    stacks[curStackIndex].clear();
}
};
