#pragma once

#include <SDL2/SDL.h>
#include "Renderer.h"

namespace Vane {
class Window {
public:
    Window();
    ~Window();

    bool createWindow(const char* title, int width, int height);
    void getWindowSize(int &w, int &h) const;
    void mainLoop() const;

private:
    SDL_Window* window = nullptr;
    Renderer* renderer = nullptr;

    void initializeRenderer(SDL_Window*);
    void cleanup() const;
};

}
