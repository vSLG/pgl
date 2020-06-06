// SPDX-License-Identifier: LGPL-3.0-or-later

#include <glm/gtc/matrix_transform.hpp>

#include <engine.hpp>
#include <util.hpp>

using namespace pgl;

// This function should be used for defining scene objects and setting up
// everything that will be used on render calls, e.g. camera and shaders.
void Engine::setup() {
    debug("(Engine) Starting setup.");

    sceneObjs.push_back(new drawable::Triangle(
        100, 100, (width) -100, 100, width / 2, height - 100));

    sceneObjs.push_back(new drawable::Circle(100, 100, 25));

    camera = new Camera(width,
                        height,
                        glm::vec3(width / 2.f, height / 2.f, 500.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
}