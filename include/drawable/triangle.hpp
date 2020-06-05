// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <drawable.hpp>

namespace pgl::drawable {
class Triangle : public Drawable {
  public:
    Triangle(glm::vec3 position, glm::vec3 shapeSize);
    Triangle(glm::vec2 position, glm::vec2 shapeSize);
    Triangle(int x, int y, int w, int h);

  private:
    const char *__name() {
        return "Triangle";
    }
};
} // namespace pgl::drawable