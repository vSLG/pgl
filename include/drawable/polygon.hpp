// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <drawable.hpp>

namespace pgl::drawable {
class Polygon : public Drawable {
  public:
    virtual glm::vec2 centroid();
    virtual void      update();

    virtual glm::vec3 pos();
    virtual bool      centered();
    virtual void      centered(bool centered);

  protected:
    bool      centered_ = true;
    glm::vec2 centroid_;
};
} // namespace pgl::drawable

// Include polygons
#include <drawable/cricle.hpp>
#include <drawable/triangle.hpp>