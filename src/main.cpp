#include <iostream>
#include <SDL2/SDL.h>
#include <Renderer.h>
#include <Window.h>
#include <glad/glad.h>
#include <fmt/core.h>

int main(int argv, char** args) {
    Window window;


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