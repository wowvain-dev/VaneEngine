#pragma once

#include "Allocator.hpp"

#include <Vane/Core/Containers/SinglyLinkedList.hpp>

namespace Vane {

class FreeListAllocator : public Allocator {
public: 
  enum PlacementPolicy {
    FIND_FIRST, 
    FIND_BEST
  };

private:
  struct FreeHeader {
    u_size blockSize;
  };
  struct AllocationHeader {
    u_size blockSize;
    char padding;
  };

  typedef SinglyLinkedList<FreeHeader>::Node Node;

  void* m_startPtr = nullptr;
  PlacementPolicy m_policy;
  SinglyLinkedList<FreeHeader> m_freeList;

public:
  FreeListAllocator(const u_size totalSize, const PlacementPolicy pPolicy);

  virtual ~FreeListAllocator();
  virtual void* Allocate(const u_size size, const u8 alignment = 8) override;
  virtual void Free(void* ptr) override;
  virtual void Init() override;
  virtual void Reset();

private:
  FreeListAllocator(FreeListAllocator &freeListAllocator);

  void Coalescence(Node *prevBlock, Node *freeBlock);

  void Find(const u_size size, const u8 alignment, u_size& padding, Node*& previousNode, Node*& foundNode);
  void FindBest(const u_size size, const u8 alignment, u_size& padding, Node*& previousNode, Node*& foundNode);
  void FindFirst(const u_size size, const u8 alignment, u_size& padding, Node*& previousNode, Node*& foundNode);
};

}