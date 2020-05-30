#include <engine.hpp>
#include <iostream>

int main(int argc, char **argv) {
    std::cout << "Hello world!\n";

    int      width          = 600;
    int      height         = 400;
    unsigned lastFrameCount = 0;

    Engine *engine = new Engine();
    engine->initInternals(width, height);

    time_t time_before = time(NULL);
    while (engine->running()) {
        engine->handleEvents();
        engine->update();
        engine->draw();

        if (time(NULL) > time_before) {
            printf("FPS: %u\n", engine->frameCount() - lastFrameCount);
            lastFrameCount = engine->frameCount();
            time_before    = time(NULL);
        }
    }

    engine->stop();

    return 0;
}