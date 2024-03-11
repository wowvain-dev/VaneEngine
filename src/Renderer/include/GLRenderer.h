#pragma once
#include "Renderer.h"

namespace Vane {
class GLRenderer : public Renderer {
public:
    SDL_GLContext glContext = nullptr;

    GLRenderer(SDL_Window* _window) : window(_window) {}
    void initialize() override;
    void render() override;
    void shutdown() override;
private:
    SDL_Window* window;
};
}
