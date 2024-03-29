#include <iostream>

#include <Core/Application.hpp>
#include <Core/Logger.hpp>
#include <Core/Memory.hpp>
#include <Platform/Platform.hpp>
#include <EntryPoint.hpp>

class Game : public Vane::Application
{
public:
    Game(Vane::ApplicationConfig config) : Vane::Application(config) {}
    void onInit()
    {
        VDEBUG("game Initialized");
    }

    void onShutdown()
    {
        VDEBUG("onShutdown called...");
    }

    void onUpdate(f32 ms)
    {
        // VDEBUG("onUpdate called...");
        Vane::Platform::sleep(2000);        
    }
};

Vane::Application* Vane::CreateApplication(int argc, char **argv)
{
    ApplicationConfig config;
    config.name = "Vane Sandbox";
    config.windowHeight = 500;
    config.windowWidth = 500;
    config.startPosX = 100;
    config.startPosY = 100;

    auto app = new Game(config);

    return app;
}
