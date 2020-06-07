// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/glm.hpp>
#include <vector>

#include <shader.hpp>

namespace pgl::drawable {

// Use this struct instead of grouping vertices in a large float array.
struct Vertex {
    Vertex(float X = 0.F, float Y = 0.F, float Z = 0.F) : x(X), y(Y), z(Z) {
    }

    Vertex(glm::vec2 pos) : Vertex(pos[0], pos[1]) {
    }
    Vertex(glm::vec3 pos) : Vertex(pos[0], pos[1], pos[2]) {
    }

    float x, y, z;

    glm::vec2 xy() {
        return glm::vec2(x, y);
    }
};

/*
 * This is an abstract class which will be used to make simple shapes like
 * squares, triangles and circles.
 */
class Drawable {
  protected:
    Drawable();

    virtual void update();
    virtual void buffersReady();
    virtual void normalizeVertices();

    Shader *            shader;
    glm::mat4           model;
    std::vector<Vertex> vertices;

    unsigned vao, vbo;
    unsigned drawMode;

    glm::vec3 pos_;
    glm::vec3 size_;

    float     rotation          = 0.f;
    glm::vec3 rotationDirection = glm::vec3(0.f, 0.f, 1.f);

    virtual const char *__name() = 0;

  public:
    virtual ~Drawable();

    // This will be called each loop by the engine.
    virtual void draw(glm::mat4 projection, glm::mat4 view);

    // Use radians and rotate around the Z axis by default.
    virtual void rotate(float radians);

    virtual void      size(glm::vec3 newSize);
    virtual void      size(glm::vec2 newSize);
    virtual void      size(int w, int h);
    virtual glm::vec3 size();

    virtual void      pos(glm::vec3 newPos);
    virtual void      pos(glm::vec2 newPos);
    virtual void      pos(int x, int y);
    virtual glm::vec3 pos();
};
}; // namespace pgl::drawable

// Included shapes.
#include <drawable/polygon.hpp>