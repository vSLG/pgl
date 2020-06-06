// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <drawable.hpp>

namespace pgl::drawable {
class Polygon : public Drawable {
  public:
    virtual glm::vec2 centroid();
    virtual glm::vec3 pos();
    virtual void      pos(glm::vec3 newPos);
    virtual void      update();
    bool              centered = true;

  protected:
    glm::vec2 centroid_;
};
} // namespace pgl::drawable

#include <drawable/triangle.hpp>