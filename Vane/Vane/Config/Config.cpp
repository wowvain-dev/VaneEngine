#include "Config.hpp"

namespace Vane {
Config* Config::s_Instance;
std::mutex Config::s_Mutex;
}
