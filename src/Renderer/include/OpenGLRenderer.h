#pragma once
#include "Renderer.h"

class OpenGLRenderer : public Renderer {
public:
    void initialize() override;
    void render() override;
    void shutdown() override;
};
