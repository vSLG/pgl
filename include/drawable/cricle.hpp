// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <drawable.hpp>

namespace pgl::drawable {
class Circle : public Polygon {
  public:
    Circle(glm::vec2 position, float radius);
    Circle(int x, int y, float radius);

    float radius();
    void  radius(float radius);

  private:
    float radius_;

    const char *__name() {
        return "Circle";
    }
};
} // namespace pgl::drawable