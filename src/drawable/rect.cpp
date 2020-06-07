// SPDX-License-Identifier: LGPL-3.0-or-later

#include <drawable/rect.hpp>

using namespace pgl::drawable;

Rect::Rect(glm::vec2 position, glm::vec2 size)
    : Quad(position,
           position + glm::vec2(0.f, size.y),
           position + size,
           position + glm::vec2(size.x, 0.f)) {
    Drawable::pos(position);
}

Rect::Rect(float x, float y, float width, float height)
    : Rect({x, y}, {width, height}) {
}