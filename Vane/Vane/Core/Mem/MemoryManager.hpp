#pragma once 

#include <mutex>
#include <array>
#include <string>

#include <Vane/Core/Defines.hpp>
#include <Vane/Core/Mem/Allocator.hpp>
#include <Vane/Core/Mem/StackAllocator.hpp>

namespace Vane {
class MemoryManager {
private:
  static MemoryManager* s_Instance;
  static std::mutex s_Mutex;

public:
  MemoryManager(MemoryManager &other) = delete;
  void operator =(const MemoryManager &) = delete;

  static MemoryManager *GetInstance();

protected:
  ~MemoryManager() = default;

private:
  MemoryManager() = default;

public:
  void Initialize();
  void Shutdown();

private:

  StackAllocator m_perFrameAllocator{256_MB};

};
}