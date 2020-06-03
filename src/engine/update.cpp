#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <engine.hpp>

using namespace pgl;

void Engine::update() {
    background(100, 100, 100);
    tempShader->use();

    glm::mat4 model(1.0f);

    camera->pos = glm::vec3(sin(glm::radians((float) _frameCount)) * 2.0f,
                            0.0f,
                            cos(glm::radians((float) _frameCount)) * 2.0f);

    tempShader->setMat4("projection", camera->projection);
    tempShader->setMat4("view", camera->view());
    tempShader->setMat4("model", model);

    glBindVertexArray(tempVao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}