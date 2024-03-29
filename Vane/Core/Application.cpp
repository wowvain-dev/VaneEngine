#include "Application.hpp"

namespace Vane
{

    Application *Application::s_Instance = nullptr;

    Application::Application(const ApplicationConfig &config)
        : m_Config(config)
    {
        // VASSERT_MSG(s_Instance != nullptr, "Instance already created.");
        if (s_Instance != nullptr) {
            VFATAL("Application instance already created.");
            return;
        }
        s_Instance = this;

        Logger::initializeLogging();

        // TODO: initialize memory manager 

        VFATAL("A test message: {}", 3.f);
        VERROR("A test message: {}", 3.f);
        VWARN("A test message: {}", 3.f);
        VINFO("A test message: {}", 3.f);
        VDEBUG("A test message: {}", 3.f);
        VTRACE("A test message: {}", 3.f);

        m_Running = true;
        m_Suspended = false;
        m_Platform = std::unique_ptr<Platform>(new Platform);
        m_Platform -> startup(
            config.name.c_str(),
            config.startPosX,
            config.startPosY,
            config.windowWidth,
            config.windowHeight
        );
    }

    Application::~Application() {
        VDEBUG("Shutting down APPLICATION");

        m_Platform.reset();

        VDEBUG("Shat down APPLICATION");
    }

    void Application::run()
    {
        onInit();
        while (m_Running)
        {
            onUpdate(1);
        }
        onShutdown();
    }

    void Application::shutdown() {
        m_Running = false;
    }
};
