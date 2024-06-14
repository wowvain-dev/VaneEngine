#include "StackAllocator.hpp"

#include "MemUtils.hpp"
#include "Vane/Core/Logger.hpp"

using namespace Vane;

StackAllocator::StackAllocator(const u_size totalSize) : Allocator(totalSize) {}

void StackAllocator::Init() {
    if (m_startPtr != nullptr) {
        operator delete(m_startPtr);
    }
    m_startPtr = operator new (m_totalSize);
    m_offset = 0;
}

void StackAllocator::Reset() {
    m_totalSize = 0;
    m_peak = 0;
    m_used = 0;
}

StackAllocator::~StackAllocator() {
    m_offset = 0;
    operator delete(m_startPtr);
}

void* StackAllocator::Allocate(u_size size, u8 alignment) {
    const u_size currentAddress = (u_size)m_startPtr + m_offset;
    u_size padding = MemUtils::CalculatePaddingWithHeader(currentAddress, alignment, sizeof(AllocationHeader));

    if (m_offset + padding + size > m_totalSize) {
        VERROR("StackAllocator: out of memory")
        return nullptr;
    }

    const u_size nextAddress = currentAddress + padding;
    const u_size headerAddress = nextAddress - sizeof(AllocationHeader);

    ((AllocationHeader*)headerAddress)->padding = (char)padding;

    m_offset += padding + size;
    m_used += padding + size;
    m_peak = m_used > m_peak ? m_used : m_peak;

    VDEBUG("StackAllocator Allocation: {} bytes @ {}\tTotal: {} bytes\tUsed: {} bytes\tFree: {} bytes", size, (void*)nextAddress, m_totalSize, m_used, m_totalSize-m_used)

    return reinterpret_cast<void *>(nextAddress);
}

void StackAllocator::Free(void* ptr) {
    const u_size headerAddress = (u_size)ptr - sizeof(AllocationHeader);
    AllocationHeader* allocationHeader = (AllocationHeader*)headerAddress;

    u_size freedAmount = 0;
    freedAmount = (u_size)m_startPtr + m_used - (u_size)ptr - (u_size)allocationHeader->padding;
    
    m_offset = (u_size)ptr - (u_size)allocationHeader->padding - (u_size)m_startPtr;
    m_used = m_offset;

    VDEBUG("StackAllocator Free: {} bytes @ {}\tTotal: {} bytes\tUsed: {} bytes\tFree: {} bytes", freedAmount, ptr, m_totalSize, m_used, m_totalSize-m_used)
    
}