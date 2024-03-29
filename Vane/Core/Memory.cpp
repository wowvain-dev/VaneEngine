#include "Memory.hpp"
#include "Defines.hpp"

using namespace Vane;


void* operator new(u32 size) { return malloc(size); }
void* operator new[](u32 size) { return malloc(size); }
void  operator delete(void* mem) noexcept { free(mem); }
void  operator delete[](void* mem) noexcept { free(mem); }

void* operator new(u32 size, Vane::Align alignment) {
    u32 adjustedSize = std::max(size, alignment.getValue());
    void* ptr = std::aligned_alloc(alignment.getValue(), adjustedSize);
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}
void* operator new[](u32 size, Vane::Align alignment) {
    return operator new(size, alignment);
}
void  operator delete(void* mem, Vane::Align alignment) noexcept {
    free(mem);
}
void  operator delete[](void* mem, Vane::Align alignment) noexcept {
    operator delete(mem, alignment);
}