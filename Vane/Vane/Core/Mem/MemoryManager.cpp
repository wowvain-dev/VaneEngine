#include "MemoryManager.hpp"

namespace Vane {

MemoryManager* MemoryManager::s_Instance = nullptr;
std::mutex MemoryManager::s_Mutex;

MemoryManager *MemoryManager::GetInstance(){
  std::lock_guard<std::mutex> lock(s_Mutex);
  if (s_Instance == nullptr) {
    s_Instance = new MemoryManager();
  }
  return s_Instance;
}

void MemoryManager::Initialize(){
  m_perFrameAllocator.Init();
}

void MemoryManager::Shutdown(){
  delete s_Instance;
}

}