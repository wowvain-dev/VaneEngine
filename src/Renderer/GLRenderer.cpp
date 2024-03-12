#include <GLRenderer.h>
#include <iostream>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <fmt/core.h>

using namespace Vane::Albita;

GLRenderer::~GLRenderer() {
    shutdown();
}

void GLRenderer::initialize() {
    glContext = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    std::cout << "OpenGL Renderer initialized. OpenGL Version: " <<
            reinterpret_cast<const char*>(glGetString(GL_VERSION)) << '\n';
}

void GLRenderer::render() {
    SDL_GL_SwapWindow(window);
    glGetError();
}

void GLRenderer::clearBuffer(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLRenderer::shutdown() {
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
    }
}
