#pragma once

#include <toml++/toml.hpp>
#include <fstream>
#include <iostream>

#ifdef _WIN32

#elif unix
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#elif __MACH__

#endif

namespace Vane {

class EngineConfig {
public:
    toml::table tbl;

public:
    void initialize();
    bool readConfig();

private:
    static toml::table defaultConfiguration();
    static std::string configPath();
};

} // Vane