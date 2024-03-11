//
// Created by wowva on 3/11/2024.
//

#include "EngineConfig.h"


namespace Vane {



bool EngineConfig::parseConfigFile() {
    auto configPath = EngineConfig::configPath();

    if (!std::filesystem::exists(configPath)) {
        return false;
    }

    try {
        _table = toml::parse_file(configPath);
        // std::cout << tbl << "\n";
    } catch (const toml::parse_error& err) {
        std::cerr << "Toml parsing error: \n" << err << "\n";
        std::throw_with_nested(err);
    }

    return true;
}

BACKEND EngineConfig::getBackend() const {
    std::optional<std::string_view> opt_backend =
        _table["engine"]["backend"].value<std::string_view>();

    if (!opt_backend.has_value()) {
        std::cerr << "Invalid `engine.backend` config value." << std::endl;
        std::cerr << "Returning default value..." << std::endl;

        return AUTO;
    }

    auto backend = opt_backend.value();

    if (backend == "DX11") {
        return DX11;
    }
    if (backend == "OPENGL") {
        return OPENGL;
    }
    if (backend == "VULKAN") {
        return VULKAN;
    }
    if (backend == "DX12") {
        return DX12;
    }

    std::cerr << "Invalid `engine.backend` config value." << std::endl;
    std::cerr << "Returning default value..." << std::endl;
    return AUTO;
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
    if (!parseConfigFile()) {
        _table = defaultConfiguration();
        auto configPath = EngineConfig::configPath();

        std::ofstream config(configPath.c_str());

        config << _table;

        config.close();
    }

    // CHECKING SYNTAX AND VALUES
}

void EngineConfig::saveChanges() const {
    auto path = configPath();
    std::ofstream config(path);

    config << _table;

    config.close();
}

} // Vane