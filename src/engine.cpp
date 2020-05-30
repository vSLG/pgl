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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    glContext = SDL_GL_CreateContext(window);

    gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);

    if (!(window && glContext))
        // TODO
        throw std::runtime_error("Could not initialize window or OpenGL context.");

    isRunning = true;
    loadAllShaders(std::getenv("srctree") + std::string("/src/shader"));
}

void Engine::background(int r, int g, int b) {
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

void Engine::stop() {
    // TODO
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
                std::cout << "Before path: " << shaderPath << "\n";
                shadersPath.insert(shaderPath);
                shaders.push_back(Shader(shaderPath));
            }
        }
    }
}