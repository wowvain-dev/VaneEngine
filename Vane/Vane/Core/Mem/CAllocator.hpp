#pragma once

#include <Vane/Core/Mem/Allocator.hpp>

namespace Vane {

class CAllocator : public Allocator {
public:
  CAllocator();

  virtual ~CAllocator();
  virtual void* Allocate(const u_size size, const u8 alignment = 0) override;
  virtual void Free(void* ptr) override;
  virtual void Init() override;
};

}