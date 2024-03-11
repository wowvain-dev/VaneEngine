#include "include/Window.h"
#include <iostream>

#include <Renderer.h>
#include <fmt/core.h>
#include "GLRenderer.h"
#include "DX11Renderer.h"

using namespace Vane;

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

bool Window::createWindow(const char *title, int width, int height, Vane::BACKEND backend) {
    if (backend == AUTO) {
#ifdef _WIN32

        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
        SDL_WINDOW_SHOWN);
#elif
        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_VULKAN);
#endif
    } else if (backend == OPENGL) {
        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_OPENGL);
    } else if (backend == VULKAN) {
        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_VULKAN);
    } else {
        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
        SDL_WINDOW_SHOWN);
    }

    if (!window) {
        std::cerr << fmt::format("Window could not be created! SDL_Error: ", SDL_GetError())
            << std::endl;
        return false;
    }

    initializeRenderer(window, backend);

    return true;
}

void Window::getWindowSize(int &w, int &h) const {
    if (window == nullptr) {
        fmt::print("getWindowSize called before window has been initialized.");
    }
    SDL_GetWindowSize(this->window, &w, &h);
}

void Window::initializeRenderer(SDL_Window* window, BACKEND backend) {
    if (backend == AUTO) {
#ifdef _WIN32
        renderer = new DX11Renderer(window);
#else
    // VULKAN IMPLEMENTATION
#endif
    } else if (backend == DX12) {
    // DX12 IMPLEMENTATION
    } else if (backend == DX11) {
        renderer = new DX11Renderer(window);
    } else if (backend == VULKAN) {
    // VULKAN IMPLEMENTATION
    } else if (backend == OPENGL) {
        renderer = new GLRenderer(window);
    }
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
