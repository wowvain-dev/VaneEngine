#include <iostream>
#include <SDL2/SDL.h>
#include <Renderer.h>
#include <Window.h>
#include <glad/glad.h>

int main(int argv, char** args) {
    Window window;

    if (window.createWindow("My game engine", 800, 600)) {
        window.mainLoop();
    }

    return 0;
}