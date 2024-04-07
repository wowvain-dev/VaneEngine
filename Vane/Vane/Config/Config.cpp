#include "Config.hpp"

namespace Vane {
Config *Config::s_Instance;
std::mutex Config::s_Mutex;

Config *Config::GetInstance() {
    std::lock_guard<std::mutex> lock(s_Mutex);
    if (s_Instance == nullptr) {
        s_Instance = new Config();
    }
    return s_Instance;
}

void Config::Read(const std::string_view &filePath) {
    
}


}
