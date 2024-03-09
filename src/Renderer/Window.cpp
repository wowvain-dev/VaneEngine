#include "include/Window.h"
#include <iostream>

#include <Renderer.h>
#include <fmt/core.h>
#include "OpenGLRenderer.h"

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

    glContext = SDL_GL_CreateContext(window);

    initializeRenderer();

    return true;
}

void Window::getWindowSize(int &w, int &h) {
    if (window == nullptr) {
        fmt::print("getWindowSize called before window has been initialized.");
    }
    SDL_GetWindowSize(this->window, &w, &h);
}

void Window::initializeRenderer() {
    renderer = new OpenGLRenderer();
    renderer->initialize();
}


void Window::mainLoop() {
    bool running = true;
    SDL_Event e;

    while(running) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }

            /// HANDLE OTHER EVENTS
        }
    }

    renderer->render();

    // For OpenGL
    SDL_GL_SwapWindow(window);
}

void Window::cleanup() {
    if (renderer) {
        renderer -> shutdown();
        delete renderer;
    }

    if (glContext) {
        SDL_GL_DeleteContext(glContext);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}
