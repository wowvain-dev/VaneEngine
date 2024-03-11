#pragma once

#include <SDL2/SDL.h>

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void initialize() = 0;
    virtual void render() = 0;
    virtual void shutdown() = 0;
};