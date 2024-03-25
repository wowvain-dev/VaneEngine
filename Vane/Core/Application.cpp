#include "Application.h"

using namespace Vane;

bool Application::initialised = false;

bool Application::create(ApplicationConfig* config) {
    if (Application::initialised) {
        VFATAL("Application::create called more than once.");
        return false;
    }

    Logger::initializeLogging();

    // TODO(wowvain-dev): Remove later, used for testing
    VFATAL("A test message: %f", 3.14f);
    VERROR("A test message: %f", 3.14f);
    VWARN("A test message: %f", 3.14f);
    VINFO("A test message: %f", 3.14f);
    VDEBUG("A test message: %f", 3.14f);
    VTRACE("A test message: %f", 3.14f);

    isRunning = true;
    isSuspended = false;

#ifdef VPLATFORM_WINDOWS
    platform = new Platform_Win32();
#elif VPLATFORM_LINUX
    platform = new Platform_Linux();
#endif

    if (!platform->startup(
        config->name.c_str(),
        config->startPosX,
        config->startPosY,
        config->startWidth,
        config->startHeight)) {
        VFATAL("Couldn't startup platform properly!");
        return false;
    }

    Application::initialised = true;

    return true;
}

bool Application::run() {
    while (isRunning) {
        if (!platform->pumpMessages()) {
            isRunning = false;
        }
    }

    isRunning = false;

    platform->shutdown();

    return true;
}
