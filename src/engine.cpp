#include <engine.hpp>
#include <stdexcept>

Engine::Engine() {
    checkSDL();
}
Engine::~Engine() {
}

void Engine::checkSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error("SDL initialization failed.");
}

void Engine::initInternals(int w, int h) {
    window = SDL_CreateWindow(
        "Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!(window && renderer))
        throw std::runtime_error("Could not initialize window or renderer.");

    background(50, 50, 50);
    isRunning = true;
}

void Engine::background(int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void Engine::stop() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Engine::update() {
    _frameCount++;
}

void Engine::draw() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
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