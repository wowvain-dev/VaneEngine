#include "Memory.hpp"
#include "Defines.hpp"

using namespace Vane;

#undef max

void* operator new(v_size size) { return malloc(size); }
void* operator new[](v_size size) { return malloc(size); }
void  operator delete(void* mem) noexcept { free(mem); }
void  operator delete[](void* mem) noexcept { free(mem); }

void* operator new(v_size size, Vane::Align alignment) {
    v_size adjustedSize = std::max(size, alignment.getValue());
    void* ptr = V_ALIGNED_ALLOC(alignment.getValue(), adjustedSize);
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}
void* operator new[](v_size size, Vane::Align alignment) {
    return operator new(size, alignment);
}
void  operator delete(void* mem, Vane::Align alignment) noexcept {
    free(mem);
}
void  operator delete[](void* mem, Vane::Align alignment) noexcept {
    operator delete(mem, alignment);
}