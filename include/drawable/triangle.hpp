// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <drawable/polygon.hpp>

namespace pgl::drawable {
class Triangle : public Polygon {
  public:
    Triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3);
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3);

  private:
    const char *__name() {
        return "Triangle";
    }
};
} // namespace pgl::drawable