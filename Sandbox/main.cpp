#include <iostream>

#include <Vane/Core/Application.hpp>
#include <Vane/Core/Mem/StackAllocator.hpp>
#include <Vane/Core/Mem/LinearAllocator.hpp>
#include <Vane/Core/Logger.hpp>
#include <Vane/EntryPoint.hpp>
#include <Vane/Platform/Platform.hpp>

class Game : public Vane::Application {
public:
    Game(const Vane::ApplicationConfig &config) : Vane::Application(config) {}

    void onInit() override { VDEBUG("game Initialized 2"); }

    void onShutdown() override { VDEBUG("onShutdown called..."); }

    void onUpdate(f32 ms) override {
        // VDEBUG("onUpdate called...");
    }
};

Vane::Application *Vane::CreateApplication(int argc, char **argv) {
    const ApplicationConfig config = {
            .startPosX = 110,
            .startPosY = 100,
            .windowWidth = 500,
            .windowHeight = 500,
            .name = "Vane Sandbox",
    };
    
    auto stackAllocator = new LinearAllocator(1024_MB);
    VDEBUG("Created LinearAllocator...")
    stackAllocator->Init();
    VDEBUG("Initialized LinearAllocator...")
    stackAllocator->Allocate(16);
    stackAllocator->Allocate(16);
    stackAllocator->Allocate(16);
    stackAllocator->Allocate(16);

    const auto app = new Game(config);
    
    return app;
}
