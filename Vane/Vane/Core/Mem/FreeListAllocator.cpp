#include "FreeListAllocator.hpp"

#include <Vane/Core/Asserts.hpp>

#include <Vane/Core/Logger.hpp>

namespace Vane {

FreeListAllocator::FreeListAllocator(const u_size totalSize, const PlacementPolicy pPolicy) : Allocator(totalSize) {
  m_policy = pPolicy;
}

void FreeListAllocator::Init() {
  if (m_startPtr != nullptr) {
    operator delete(m_startPtr);
    m_startPtr = nullptr;
  }

  m_startPtr = operator new(m_totalSize);

  this -> Reset();
}

FreeListAllocator::~FreeListAllocator() {
  operator delete(m_startPtr);
  m_startPtr = nullptr;
}

void* FreeListAllocator::Allocate(const u_size size, const u8 alignment) {
  const u_size allocationHeaderSize = sizeof(FreeListAllocator::AllocationHeader);
  const u_size freeHeaderSize = sizeof(FreeListAllocator::FreeHeader);

  VASSERT_MSG(size >= sizeof(Node), "Allocation size must be bigger")  
  VASSERT_MSG(alignment >= 8, "Not enough memory")

  u_size padding;
  Node* affectedNode,
      * previousNode;

  this->Find(size, alignment, padding, previousNode, affectedNode);

  VASSERT_MSG(affectedNode != nullptr, "Not enough memory")

  const u_size alignmentPadding = padding - allocationHeaderSize;
  const u_size requiredSize = size + padding;

  const u_size rest = affectedNode->data.blockSize - requiredSize;

  if (rest > 0) {
    Node* newFreeNode = reinterpret_cast<Node*>(reinterpret_cast<u_size>(affectedNode) +requiredSize);
    newFreeNode->data.blockSize = rest;
    m_freeList.insert(affectedNode, newFreeNode);
  }

  m_freeList.remove(previousNode, affectedNode);

  const u_size headerAddress = (u_size) affectedNode + alignmentPadding;
  const u_size dataAddress = headerAddress + allocationHeaderSize;

  ((FreeListAllocator::AllocationHeader*)headerAddress)->blockSize = requiredSize;
  ((FreeListAllocator::AllocationHeader*)headerAddress)->padding = alignmentPadding;

  m_used += requiredSize;
  m_peak = m_used > m_peak ? m_used : m_peak;

  VDEBUG("FreeListAllocator Allocation: {} bytes @ {}\tTotal: {} bytes\tUsed: {} bytes\tFree: {} bytes", size, (void*)dataAddress, m_totalSize, m_used, m_totalSize-m_used)

  return (void*) dataAddress;
}

void FreeListAllocator::Find(const u_size size, const u8 alignment, u_size& padding, Node*& previousNode, Node*& foundNode) {
  // TODO(wowvain-dev)
}

}
