#include "LinearAllocator.hpp"

#include <Vane/Core/Logger.hpp>
#include <Vane/Core/Mem/MemUtils.hpp>

using namespace Vane;

LinearAllocator::LinearAllocator(const u_size totalSize) : Allocator(totalSize) {}

void LinearAllocator::Init() {
  if (m_startPtr != nullptr) {
    operator delete(m_startPtr);
  }
  m_startPtr = operator new(m_totalSize);
  m_offset = 0;
}

void LinearAllocator::Reset() {
  m_totalSize = 0;
  m_peak = 0;
  m_used = 0;
}

LinearAllocator::~LinearAllocator() {
  m_offset = 0;
  operator delete(m_startPtr);
}

void* LinearAllocator::Allocate(u_size size, u8 alignment) {
  const u_size currentAddress = (u_size)m_startPtr + m_offset;
  u_size padding = 0;

  if (alignment != 0 && m_offset % alignment != 0) {
    padding = MemUtils::CalculatePadding(currentAddress, alignment);    
  }

  if (m_offset + padding + size > m_totalSize) {
    VERROR("LinearAllocator: out of memory")
    return nullptr;
  }

  const u_size nextAddress = currentAddress + padding;
  
  m_offset += padding + size;
  m_used += padding + size;
  m_peak = m_used > m_peak ? m_used : m_peak;

  VDEBUG("LinearAllocator Allocation: {} bytes @ {}\tTotal: {} bytes\tUsed: {} bytes\tFree: {} bytes", size, (void*)nextAddress, m_totalSize, m_used, m_totalSize-m_used)

  return reinterpret_cast<void*>(nextAddress);
}

void LinearAllocator::Free(void* ptr) {
  VERROR("LinearAllocator: Free not supported")
}
