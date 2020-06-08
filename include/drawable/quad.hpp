// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <drawable/polygon.hpp>

namespace pgl::drawable {
class Quad : public Polygon {
  public:
    Quad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4);
    Quad(float x1,
         float y1,
         float x2,
         float y2,
         float x3,
         float y3,
         float x4,
         float y4);
    ~Quad();

    void draw(glm::mat4 projection, glm::mat4 view);

  private:
    unsigned ebo;

  protected:
    virtual const char *__name() {
        return "Quad";
    }
};
} // namespace pgl::drawable

// Included shades
#include <drawable/rect.hpp>