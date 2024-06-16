#include "CAllocator.hpp"

using namespace Vane;

CAllocator::CAllocator(): Allocator(0) {}

CAllocator::~CAllocator() {}

void CAllocator::Init() {}

void* CAllocator::Allocate(const u_size size, const u8 alignment) {
  return malloc(size);
}

void CAllocator::Free(void* ptr) {
  free(ptr);
}