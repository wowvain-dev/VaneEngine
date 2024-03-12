#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "Renderer.h"
#include "types.h"

namespace Vane::Albita {
class Window {
public:
    Window();
    ~Window();

    bool createWindow(const char* title, int width, int height, BACKEND backend);
    void getWindowSize(int& w, int& h) const;
    void inputLoop(bool& running) const;

    std::shared_ptr<Renderer> renderer = nullptr;

    void shutdown();

private:
    SDL_Window* window = nullptr;

    void initializeRenderer(BACKEND);
};
}
