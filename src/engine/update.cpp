#include <engine.hpp>

void Engine::update() {
    background(100, 100, 100);

    shaders[0]->use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}