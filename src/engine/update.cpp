#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <engine.hpp>

using namespace pgl;

void Engine::update() {
    background(100, 100, 100);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(5.0f);
    tempShader->use();

    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);

    camera->pos = glm::vec3(
        sin(glm::radians((float) _frameCount)), 0.0f, cos(glm::radians((float) _frameCount)));
    view = camera->view();

    tempShader->setMat4("projection", projection);
    tempShader->setMat4("view", view);
    tempShader->setMat4("model", model);

    glBindVertexArray(tempVao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}