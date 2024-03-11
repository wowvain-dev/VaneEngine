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

    std::cout << engine.config.tbl << std::endl;

    Vane::Window window;


#ifdef USE_OPENGL
    fmt::print("Using OpenGL\n");
#elif USE_DIRECTX
    fmt::print("Using DirectX\n");
#endif

    if (window.createWindow("My game engine", 1350, 900)) {
        window.mainLoop();
    }

    return 0;
}