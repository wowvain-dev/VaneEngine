#pragma once

#include <toml++/toml.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "types.h"

#ifdef _WIN32

#elif unix
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#elif __MACH__

#endif

namespace Vane {
class EngineConfig {
    toml::table _table;

public:
    void initialize();
    bool parseConfigFile();

    Albita::BACKEND getBackend();

private:
    void saveChanges() const;
    static toml::table defaultConfiguration();
    static std::string configPath();
};
} // Vane
