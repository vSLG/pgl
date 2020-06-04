// SPDX-License-Identifier: LGPL-3.0-or-later

#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <engine.hpp>

using namespace pgl;

// This function should be used for updating scene objects.
void Engine::update() {
    background(100, 100, 100);
    tempShader->use();

    glm::mat4 model(1.0f);
    /* model = glm::rotate(
        model, glm::radians(_frameCount / 10.0f), glm::vec3(0., 0., 1.)); */

    // Let the shaders do the matrix product.
    tempShader->setMat4("projection", camera->projection);
    tempShader->setMat4("view", camera->view());
    tempShader->setMat4("model", model);

    // And draw our simple colorful triangle.
    glBindVertexArray(tempVao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}