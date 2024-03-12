#pragma once
#include "EngineConfig.h"

#include <Renderer.h>
#include <Window.h>

namespace Vane {
class Engine {
public:
    EngineConfig config;

private:
    std::shared_ptr<Albita::Renderer> renderer;
    std::shared_ptr<Albita::Window> window;

public:
    Engine();
    ~Engine();

    void run();
    void shutdown();

private:
    void mainLoop() const;
    void initialize();
};
}
