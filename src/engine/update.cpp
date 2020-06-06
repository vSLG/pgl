// SPDX-License-Identifier: LGPL-3.0-or-later

#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <engine.hpp>

using namespace pgl;

// This function should be used for updating scene objects.
void Engine::update() {
    background(100, 100, 100);

    for (drawable::Drawable *item : sceneObjs) {
        // Test funny transformations
        item->size(tan(deltaCounter * 2) * width / 2.f + width / 2.f,
                   tan(deltaCounter * 2) * height / 2.f + height / 2.f);
        item->pos(glm::vec3(tan(deltaCounter * 2) * width / 2.f + width / 2.f,
                            sin(deltaCounter * 2) * height / 2.f + height / 2.f,
                            0.f));
        item->rotate(tan(deltaCounter * 2 + 2 * M_PI / 3));
        item->draw(camera->projection(), camera->view());
    }
}