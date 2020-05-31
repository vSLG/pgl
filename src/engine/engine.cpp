#include <filesystem>
#include <iostream>
#include <set>
#include <stdexcept>

#include <engine.hpp>
#include <util.hpp>

#include <glad/glad.h>

namespace fs = std::filesystem;

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
    window = SDL_CreateWindow(
        "Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    glContext = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
        die("Could not initalize OpenGL.", false);

    if (!(window && glContext))
        die("Could not initialize window or OpenGL context.", false);

    printf("%s\n", glGetString(GL_VERSION));

    loadAllShaders(std::getenv("srctree") + std::string("/resources/shader"));

    setup();
    isRunning = true;
}

void Engine::background(int r, int g, int b) {
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::stop() {
    // TODO
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    // Cleaning shaders
    for (Shader *e : shaders)
        glDeleteProgram(e->id);

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

    SDL_PollEvent(&e);

    switch (e.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

bool Engine::running() {
    return isRunning;
}

unsigned Engine::frameCount() {
    return _frameCount;
}

void Engine::loadAllShaders(const std::string &dir) {
    std::set<std::string> shadersPath;
    for (const auto &entry : fs::directory_iterator(dir)) {
        std::vector<std::string> pathParts = Utils::split(entry.path(), '.');

        if (Shader::supportedShaderExt.find(pathParts.back()) != Shader::supportedShaderExt.end()) {
            pathParts.pop_back();
            std::string shaderPath = Utils::join(pathParts, '.');
            if (shadersPath.find(shaderPath) == shadersPath.end()) {
                shadersPath.insert(shaderPath);
                shaders.push_back(new Shader(shaderPath));
            }
        }
    }
}

void Engine::die(const std::string &message, bool _stop = false) {
    if (_stop)
        stop();
    throw std::runtime_error(message);
}