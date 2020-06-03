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
    debug_assert("(Engine) Checking if SDL can be initalized.");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        die("SDL_VIDEO initialization failed.", false);
}

void Engine::initInternals(int w, int h) {
    debug("(Engine) Creating window object.");
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

    debug("(Engine) Creating OpenGL context.");
    glContext = SDL_GL_CreateContext(window);

    debug("(Engine) Loading OpenGL functions.");
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
        die("Could not initalize OpenGL.", false);

    debug_assert("(Engine) Checking if window and OpenGL context were "
                 "initalizated successfully");
    if (!(window && glContext))
        die("Could not initialize window or OpenGL context.", false);

    width  = w;
    height = h;

    debug("(Engine) Used OpenGL version: %s", glGetString(GL_VERSION));

    SDL_SetRelativeMouseMode(SDL_TRUE);
    setup();
    isRunning = true;
}

void Engine::background(int r, int g, int b) {
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::stop() {
    debug("(Engine) Stopping engine.");

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
                debug("(Engine) Quit request received.");
                isRunning = false;
                break;
            case SDL_MOUSEMOTION:
                camera->mouseMotion(&e.motion);
                break;
            case SDL_KEYDOWN:
            default:
                break;
        }
    }

    camera->keyboardInput(SDL_GetKeyboardState(NULL), deltaTime);
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
    error("(Engine) %s", message.c_str());
    throw std::runtime_error(message);
}