#include <engine.hpp>
#include <iostream>

int main(int argc, char **argv) {
    std::cout << "Hello world!\n";

    int width  = 600;
    int height = 400;

    Engine *engine = new Engine();
    engine->initInternals(width, height);

    while (engine->running()) {
        engine->handleEvents();
        engine->update();

        // engine->background(255, 0, 0);
        engine->draw();
    }

    engine->stop();

    return 0;
}