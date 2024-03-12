#include "EngineConfig.h"


namespace Vane {
bool EngineConfig::parseConfigFile() {
    const std::string configPath = EngineConfig::configPath();

    if (!std::filesystem::exists(configPath)) {
        return false;
    }

    try {
        _table = toml::parse_file(configPath);
        // std::cout << tbl << "\n";
    }
    catch (const toml::parse_error& err) {
        std::cerr << "Toml parsing error: \n" << err << "\n";
        std::throw_with_nested(err);
    }

    return true;
}

Albita::BACKEND EngineConfig::getBackend() {
    std::optional<std::string_view> opt_backend =
            _table["engine"]["backend"].value<std::string_view>();

    if (!opt_backend.has_value()) {
        std::cerr << "\nInvalid `engine.backend` config value.\n";
        std::cerr << "Setting the file back to defaults.\n";

        std::ofstream config(configPath().c_str());

        _table = defaultConfiguration();
        config << _table;

        config.close();

        opt_backend = _table["engine"]["backend"].value<std::string_view>();
    }

    /// Even if we use `.value_or("VULKAN")`, it is impossible to get the `_or` value
    /// since in the case that no value initially existed, we replaced the config with
    /// the defaul valid one.
    const std::string_view backend = opt_backend.value_or("VULKAN");

    using namespace Albita;

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

    std::cerr << "Invalid `engine.backend` config value.\n";
    std::cerr << "Returning default value...\n";

    std::ofstream config(configPath().c_str());

    _table = defaultConfiguration();
    config << _table;

    config.close();

#ifdef _WIN32
    return DX11;
#else
    returne VULKAN;
#endif
}


toml::table EngineConfig::defaultConfiguration() {
    auto defaults = toml::table{
        {
            "engine", toml::table{
#ifdef _WIN32
                {"backend", "DX11"}
#else
            {"backend", "VULKAN"}
#endif
            }
        }
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
    }
    else {
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
    const auto configPathStr = configPath();
    const auto path = configPathStr.c_str();
    std::ofstream config(path);

    config << _table;

    config.close();
}
} // Vane
