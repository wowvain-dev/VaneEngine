#include "include/Window.h"
#include <iostream>

#include <Renderer.h>
#include <fmt/core.h>
#include "GLRenderer.h"
#include "DX11Renderer.h"

using namespace Vane::Albita;

Window::Window() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not be initialized! SDL_error: " << SDL_GetError()
                << '\n';
    }
}

Window::~Window() {
    shutdown();
}

bool Window::createWindow(const char* title, int width, int height, BACKEND backend) {
    if (backend == OPENGL) {
        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_OPENGL);
    }
    else if (backend == VULKAN) {
        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_VULKAN);
    }
    else {
        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_SHOWN);
    }

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
                << '\n';
        return false;
    }

    initializeRenderer(backend);

    return true;
}

void Window::getWindowSize(int& w, int& h) const {
    if (window == nullptr) {
        std::cout << "\ngetWindowSize called before window has been initialized.";
    }
    SDL_GetWindowSize(this->window, &w, &h);
}

void Window::initializeRenderer(BACKEND backend) {
    if (backend == DX12) {
        // DX12 IMPLEMENTATION
    }
    else if (backend == DX11) {
        renderer = std::make_shared<DX11Renderer>(window);
    }
    else if (backend == VULKAN) {
        // VULKAN IMPLEMENTATION
    }
    else if (backend == OPENGL) {
        renderer = std::make_shared<GLRenderer>(window);
    }
    renderer->initialize();
}


void Window::inputLoop(bool& running) const {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        /// HANDLE OTHER EVENTS
    }
}

void Window::shutdown() {
    std::cout << "\nShutting down window";
    if (renderer != nullptr) {
        renderer.reset();
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}
