#pragma once

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void initialize() = 0;
    virtual void render() = 0;
    virtual void shutdown() = 0;
};