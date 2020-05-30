#include <engine.hpp>
#include <stdexcept>

#include <GL/gl.h>

Engine::Engine() {
    checkSDL();
}
Engine::~Engine() {
}

void Engine::checkSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("SDL_VIDEO initialization failed.");
}

void Engine::initInternals(int w, int h) {
    window = SDL_CreateWindow("Engine",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              w,
                              h,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    glContext = SDL_GL_CreateContext(window);

    if (!(window && glContext))
        throw std::runtime_error("Could not initialize window or OpenGL context.");

    isRunning = true;
}

void Engine::background(int r, int g, int b) {
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

void Engine::stop() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::update() {
    _frameCount++;
}

void Engine::draw() {
    // glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    background(100, 100, 100);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

void Engine::handleEvents() {
    SDL_Event e;

    SDL_PollEvent(&e);

    switch (e.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}