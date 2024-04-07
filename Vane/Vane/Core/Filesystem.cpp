#include "Filesystem.hpp"

namespace Vane {
Filesystem* Filesystem::s_Instance;
std::mutex Filesystem::s_Mutex;

Filesystem *Filesystem::GetInstance() {
    std::lock_guard<std::mutex> lock(s_Mutex);
    if (s_Instance == nullptr) {
        s_Instance = new Filesystem();
    }
}


};
