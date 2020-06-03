#include <iostream>
#include <stdexcept>

#include <engine.hpp>
#include <util.hpp>

#include <glad/glad.h>

using namespace pgl;

Engine::Engine() {
    checkSDL();

    isRunning   = false;
    _frameCount = 0;
}

Engine::~Engine() {
    stop();
}

void Engine::checkSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        die("SDL_VIDEO initialization failed.", false);
}

void Engine::initInternals(int w, int h) {
    window = SDL_CreateWindow("Engine",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              w,
                              h,
                              SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    glContext = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
        die("Could not initalize OpenGL.", false);

    if (!(window && glContext))
        die("Could not initialize window or OpenGL context.", false);

    width  = w;
    height = h;

    printf("%s\n", glGetString(GL_VERSION));

    SDL_SetRelativeMouseMode(SDL_TRUE);
    setup();
    isRunning = true;
}

void Engine::background(int r, int g, int b) {
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::stop() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::draw() {
    SDL_GL_SwapWindow(window);
    _frameCount++;
}

void Engine::handleEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEMOTION:
                camera->mouseMotion(e.motion);
            default:
                break;
        }
    }
}

bool Engine::running() {
    return isRunning;
}

unsigned Engine::frameCount() {
    return _frameCount;
}

void Engine::die(const std::string &message, bool _stop = false) {
    if (_stop)
        stop();
    throw std::runtime_error(message);
}