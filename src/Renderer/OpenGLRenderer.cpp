#include <OpenGLRenderer.h>
#include <iostream>
#include <glad/glad.h>
#include <SDL2/SDL.h>

void OpenGLRenderer::initialize() {
    if (!gladLoadGLLoader(static_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    std::cout << "OpenGL Renderer initialized. OpenGL Version: "
        << glGetString(GL_VERSION) << std::endl;
}

void OpenGLRenderer::render() {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


}

void OpenGLRenderer::shutdown() {

}


