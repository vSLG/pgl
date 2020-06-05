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
        // item->setSize(sin(deltaCounter * 2) * 400, cos(deltaCounter * 2) *
        // 400); item->rotate(deltaCounter * 2);
        item->draw(camera->projection(), camera->view());
    }
}