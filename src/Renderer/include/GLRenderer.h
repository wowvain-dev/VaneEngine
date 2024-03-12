#pragma once
#include "Renderer.h"

namespace Vane::Albita {
class GLRenderer : public Renderer {
public:
    SDL_GLContext glContext = nullptr;

    GLRenderer(SDL_Window* _window) : window(_window) {}
    ~GLRenderer();

    void initialize() override;
    void render() override;
    void shutdown() override;
    void clearBuffer(float r, float g, float b) override;

private:
    SDL_Window* window;
};
}
