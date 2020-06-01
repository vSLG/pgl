#include <iostream>

#include <engine.hpp>
#include <resource/manager.hpp>

using namespace ProcessingGL;

int main(int argc, char **argv) {
    std::cout << "Hello world!\n";

    Resources::initResources();
    /* std::cout << Resources::getShaderCode(Shader::simple, Shader::vert);
    std::cout << Resources::getShaderCode(Shader::simple, Shader::vert); */

    int      width          = 600;
    int      height         = 600;
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