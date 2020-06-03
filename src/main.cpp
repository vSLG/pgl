#include <iostream>

#include <engine.hpp>
#include <resource/manager.hpp>

using namespace pgl;

int main(int argc, char **argv) {
    std::cout << "Hello world!\n";

    res::initResources();

    int      width          = 600;
    int      height         = 600;
    unsigned lastFrameCount = 0;
    float    deltaCounter   = 0.0f;

    Engine *engine = new Engine();
    engine->initInternals(width, height);

    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t last;
    while (engine->running()) {
        last = now;
        now  = SDL_GetPerformanceCounter();
        engine->deltaTime =
            (now - last) / (float) SDL_GetPerformanceFrequency();

        if (deltaCounter >= 1.0f) {
            printf("FPS: %u; delta: %f\r", lastFrameCount, engine->deltaTime);
            fflush(stdout);
            lastFrameCount = 0;
            deltaCounter   = 0;
        }

        engine->handleEvents();
        engine->update();
        engine->draw();

        deltaCounter += engine->deltaTime;
        lastFrameCount++;
    }

    engine->stop();

    return 0;
}