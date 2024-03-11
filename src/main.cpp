#include <iostream>
#include <SDL2/SDL.h>
#include <Renderer.h>
#include <Window.h>
#include <glad/glad.h>
#include <fmt/core.h>
#include <toml++/toml.hpp>
#include <string>

#include "Engine.h"

// OS SPECIFIC IMPORTS
#ifdef _WIN32

#elif unix
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#elif __MACH__

#endif

int main(int argv, char** args) {
    std::string configPath;

    Vane::Engine engine;

    auto activeBackend = engine.config.getBackend();


    Vane::Window window;


    if (window.createWindow("My game engine", 1350, 900, activeBackend)) {
        window.mainLoop();
    }

    return 0;
}