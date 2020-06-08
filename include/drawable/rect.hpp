// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <drawable/quad.hpp>

namespace pgl::drawable {
class Rect : public Quad {
  public:
    Rect(glm::vec2 position, glm::vec2 size);
    Rect(float x, float y, float width, float height);
};
} // namespace pgl::drawable