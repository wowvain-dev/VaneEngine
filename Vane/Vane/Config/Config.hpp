#pragma once

#include <mutex>
#include <string>

#include <Vane/Core/Memory/MemoryManager.hpp>

namespace Vane {
class Config {
private:
    static Config* s_Instance;
    static std::mutex s_Mutex;

public:
    Config(Config& other) = delete;
    void operator =(const Config&) = delete;
};
}
