#include "Application.hpp"

namespace Vane {
Application* Application::s_Instance = nullptr;

Application::Application(const ApplicationConfig& config)
    : m_Config(config) {
    // VASSERT_MSG(s_Instance != nullptr, "Instance already created.");
    if (s_Instance != nullptr) {
        VFATAL("Application instance already created.");
        return;
    }
    s_Instance = this;

    Logger::initializeLogging();

    VDEBUG("this is no longer a test 3");

    m_Running = true;
    m_Suspended = false;
    m_Platform = std::unique_ptr<Platform>(new Platform);
    m_Platform->startup(
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

void Application::run() {
    onInit();
    while (m_Running) {
        m_Platform->pumpMessages();
        onUpdate(1);
    }
    onShutdown();
}

void Application::shutdown() {
    m_Running = false;
}
};
