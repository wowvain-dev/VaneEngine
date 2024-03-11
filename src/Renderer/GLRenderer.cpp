#include <GLRenderer.h>
#include <iostream>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <fmt/core.h>

using namespace Vane;

void GLRenderer::initialize() {
    glContext = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    fmt::print("OpenGL Renderer initialized. OpenGL Version: {}\n",
        reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void GLRenderer::render() {
    glClearColor(1.f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
    glGetError();
}

void GLRenderer::shutdown() {
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
    }
}


