// SPDX-License-Identifier: LGPL-3.0-or-later

#include <iostream>

#include <engine.hpp>
#include <resource/manager.hpp>
#include <util.hpp>

using namespace pgl;

int main(int argc, char **argv) {
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    res::initResources();

    int   width        = 600;
    int   height       = 600;
    float deltaCounter = 0.0f;

    Engine *engine = new Engine();
    engine->initInternals(width, height);

    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t last;

    debug("(main) Starting main loop.");
    while (engine->running()) {
        last = now;
        now  = SDL_GetPerformanceCounter();
        engine->deltaTime =
            (now - last) / (float) SDL_GetPerformanceFrequency();
        deltaCounter += engine->deltaTime;

        if (deltaCounter >= 0.5f) {
            debug("(main) FPS: %0.2f; delta: %f\r",
                  1.0f / engine->deltaTime,
                  engine->deltaTime);
            deltaCounter = 0;
        }

        engine->handleEvents();
        engine->update();
        engine->draw();
    }

    debug("(main) Exited main loop.");

    engine->stop();

    return 0;
}