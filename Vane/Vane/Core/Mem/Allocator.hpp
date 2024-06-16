#pragma once

#include <Vane/Core/Defines.hpp>

namespace Vane {
class Allocator {
protected:
    u_size m_totalSize;
    u_size m_used;
    u_size m_peak;
public:
    Allocator(const u_size totalSize) : m_totalSize{totalSize}, m_used{0}, m_peak{0} {}
    virtual ~Allocator() { m_totalSize = 0; }
    virtual void* Allocate(const u_size size, const u8 alignment = 4) = 0;
    virtual void Free(void* ptr) = 0;
    virtual void Init() = 0;

    friend class MemoryBenchmark;
};
}