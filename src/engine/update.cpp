#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <engine.hpp>

using namespace pgl;

void Engine::update() {
    background(100, 100, 100);
    tempShader->use();

    glm::mat4 model(1.0f);
    /* model = glm::rotate(
        model, glm::radians(_frameCount / 10.0f), glm::vec3(0., 0., 1.)); */

    tempShader->setMat4("projection", camera->projection);
    tempShader->setMat4("view", camera->view());
    tempShader->setMat4("model", model);

    glBindVertexArray(tempVao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}