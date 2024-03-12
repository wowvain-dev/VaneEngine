#include "Engine.h"

#include "fmt/chrono.h"

namespace Vane {
Engine::Engine() {
    initialize();
}

Engine::~Engine() { shutdown(); }

void Engine::initialize() {
    config.initialize();

    std::cout << "\nAfter config.initizliaze()\n";

    window = std::make_shared<Albita::Window>();

    std::cout << "\nAfter making the window shared pointer.()\n";

    const auto backend = config.getBackend();


    if (window->createWindow("VaneEngine", 1350, 900, backend)) {
        renderer = window->renderer;
    }
    else {
        throw std::runtime_error("Failed to create window. Aborting");
    }
}

void Engine::mainLoop() const {
    bool windowRunning = true;

    while (windowRunning) {
        window->inputLoop(windowRunning);
        renderer->clearBuffer(0.3f, 0.5f, 0.0f);
        renderer->render();
    }
}

void Engine::run() {
    std::cout << "\nVane engine started...\n\tUSING:\t"
            << Albita::STRING_FROM_BACKEND(config.getBackend()) << '\n';
    mainLoop();
    std::cout << "\nStopped running...\n";
}

void Engine::shutdown() {
    std::cout << "\nShutting down engine.";
    if (renderer != nullptr) {
        renderer.reset();
    }
    if (window != nullptr) {
        window.reset();
    }
}
}
