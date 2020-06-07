// SPDX-License-Identifier: LGPL-3.0-or-later

#include <iostream>
#include <stdexcept>

#include <engine.hpp>
#include <util.hpp>

#include <glad/glad.h>

using namespace pgl;

Engine::Engine() {
    checkSDL();

    isRunning    = false;
    deltaCounter = 0.f;
}

Engine::~Engine() {
    stop();
}

void Engine::checkSDL() {
    debug_assert("(Engine) Checking if SDL can be initalized.");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        die("SDL_VIDEO initialization failed.", false);
}

// Initalize everything we need to get a running OpenGL SDL window.
void Engine::initInternals(int w, int h) {
    debug("(Engine) Creating window object.");

    // Create SDL window. The last param, we specify flags for certain window
    // features, e.g. it should be resizeable, or full screen, etc.
    window = SDL_CreateWindow("Engine",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              w,
                              h,
                              SDL_WINDOW_OPENGL);

    // Specify OpenGL version to SDL (really useful?), and tell that we want to
    // use core profile from OpenGL.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    debug("(Engine) Creating OpenGL context.");
    glContext = SDL_GL_CreateContext(window);

    // Load OpenGL functions with GLAD, since OpenGL functions are defined at
    // runtime.
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

    setup();
    isRunning = true;
}

// Abstraction for setting background color.
void Engine::background(int r, int g, int b) {
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // We may want to clear depth buffer later.
}

void Engine::stop() {
    debug("(Engine) Stopping engine.");

    // Free memory, do not leak.
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::draw() {
    SDL_GL_SwapWindow(window);
    deltaCounter += deltaTime;
}

void Engine::handleEvents() {
    SDL_Event e;

    // Using while loop is important. Events accumulate in a queue, and if we
    // treat one of them each frame, we delay other events.
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                debug("(Engine) Quit request received.");
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        debug("(Engine) Quit request received.");
                        isRunning = false;
                        break;
                    case SDLK_r:
                        reset();
                        break;
                    case SDLK_q:
                        toggleWireframe();
                        break;
                    case SDLK_t:
                        camera->toggleProjection();
                        break;
                    case SDLK_EQUALS:
                        camera->addZoom();
                        break;
                    case SDLK_MINUS:
                        camera->removeZoom();
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                camera->mouseMotion(&e.motion);
                break;
            default:
                break;
        }
    }

    // Treat keyboard events without polling event. Since polling a keyboard
    // event gives us a normal OS keyboard events, we do not have smooth
    // movement. So treat keyboard events as key states.
    // This call must be performed after polling events, else key states will
    // not be available.
    camera->keyboardInput(SDL_GetKeyboardState(NULL), deltaTime);
}

bool Engine::running() {
    return isRunning;
}

void Engine::die(const std::string &message, bool _stop = false) {
    if (_stop)
        stop();
    error("(Engine) %s", message.c_str());
    throw std::runtime_error(message);
}

void Engine::toggleWireframe() {
    wireframe = !wireframe;
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
}

void Engine::reset() {
    delete camera;
    wireframe = false;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (drawable::Drawable *obj : sceneObjs)
        delete obj;
    sceneObjs.clear();
    setup();
}