//
// Created by wowva on 3/11/2024.
//

#include "EngineConfig.h"

#include <filesystem>

namespace Vane {

bool EngineConfig::readConfig() {
    auto configPath = EngineConfig::configPath();

    if (!std::filesystem::exists(configPath)) {
        return false;
    }

    try {
        tbl = toml::parse_file(configPath);
        // std::cout << tbl << "\n";
    } catch (const toml::parse_error& err) {
        std::cerr << "Toml parsing error: \n" << err << "\n";
        std::throw_with_nested(err);
    }

    return true;
}

toml::table EngineConfig::defaultConfiguration() {
    auto defaults = toml::table {
        {"engine", toml::table {
                {"backend", "auto"}
        }}
    };

    return defaults;
}

std::string EngineConfig::configPath() {
    std::string configPath;

    /// OS SPECIFIC CONFIGURATION
    /// THREAD UNSAFE CURRENTLY, LOOK INTO IT LATER
#ifdef _WIN32
    char* buffer;
    size_t sz = 0;
    if (_dupenv_s(&buffer, &sz, "USERPROFILE") == 0 && buffer != nullptr) {
        configPath.append(buffer);
        free(buffer);
    } else {
        throw std::runtime_error("Could not find %USERPROFILE% environment variable.");
    }
#elif unix
    char* homedir;
    if ((homedir == getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid()) -> pw_dir;
    }
#elif __MACH__
    char* homedir;
    if ((homedir == getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid()) -> pw_dir;
    }
#endif

    configPath.append("/vane.toml");

    return configPath;
}

void EngineConfig::initialize() {
    if (!readConfig()) {
        tbl = defaultConfiguration();
        auto configPath = EngineConfig::configPath();

        std::ofstream config(configPath.c_str());

        config << tbl;

        config.close();
    }

    // CHECKING SYNTAX AND VALUES
}


} // Vane