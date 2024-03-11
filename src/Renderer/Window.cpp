#include "include/Window.h"
#include <iostream>

#include <Renderer.h>
#include <fmt/core.h>
#include "GLRenderer.h"
#include "DX11Renderer.h"

Window::Window() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr
            << fmt::format("SDL could not be initialized! SDL_error: {}", SDL_GetError())
            << std::endl;
    }
}

Window::~Window() {
    cleanup();
}

bool Window::createWindow(const char *title, int width, int height) {
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
#ifdef USE_OPENGL
        SDL_WINDOW_OPENGL
#elif USE_VULKAN
        SDL_WINDOW_VULKAN
#else
        SDL_WINDOW_SHOWN
#endif
        );

    if (!window) {
        std::cerr << fmt::format("Window could not be created! SDL_Error: ", SDL_GetError())
            << std::endl;
        return false;
    }

    initializeRenderer(window);

    return true;
}

void Window::getWindowSize(int &w, int &h) const {
    if (window == nullptr) {
        fmt::print("getWindowSize called before window has been initialized.");
    }
    SDL_GetWindowSize(this->window, &w, &h);
}

void Window::initializeRenderer(SDL_Window* window) {
#ifdef USE_OPENGL
    renderer = new GLRenderer(window);
#elif USE_DIRECTX
    renderer = new DirectXRenderer(window);
#else
    // TODO(wowvain-dev): add Vulkan renderer;
#endif


    renderer->initialize();
}


void Window::mainLoop() const {
    bool running = true;
    SDL_Event e;

    while(running) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }

            /// HANDLE OTHER EVENTS
        }
        renderer->render();
    }

}

void Window::cleanup() const {
    if (renderer) {
        renderer -> shutdown();
        delete renderer;
    }

    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}
