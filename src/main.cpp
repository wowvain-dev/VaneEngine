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
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

int main(int argv, char** args) {
    try {
        std::cout << "Starting engine...\n";

        Vane::Engine engine;

        engine.run();
    }
    catch (std::exception& ex) {
        std::cout << "Caught exception: " << ex.what() << '\n';
    }
    return 0;
}
