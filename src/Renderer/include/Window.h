#pragma once

#include <SDL2/SDL.h>
#include "Renderer.h"

class Window {
public:
    Window();
    ~Window();

    bool createWindow(const char* title, int width, int height);
    void getWindowSize(int &w, int &h);
    void mainLoop();

private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    Renderer* renderer = nullptr;

    void initializeRenderer();
    void cleanup();
};

