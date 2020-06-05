// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/glm.hpp>
#include <vector>

#include <shader.hpp>

namespace pgl::drawable {

// Use this struct instead of grouping vertices in a large float array.
struct ColoredVertex {
    ColoredVertex(float X = 0.F,
                  float Y = 0.F,
                  float Z = 0.F,
                  float R = 0.f,
                  float G = 0.f,
                  float B = 0.f,
                  float A = 0.f)
        : x(X), y(Y), z(Z), r(R), g(G), b(B), a(A) {
    }
    float x, y, z, r, g, b, a;
};

/*
 * This is an abstract class which will be used to make simple shapes like
 * squares, triangles and circles.
 */
class Drawable {
  protected:
    Drawable(glm::vec3 position, glm::vec3 shapeSize);
    Drawable(glm::vec2 position, glm::vec2 shapeSize);
    Drawable(int x, int y, int w, int h);
    ~Drawable();

    void update();
    void buffersReady();

    Shader *                   shader;
    glm::mat4                  model;
    std::vector<ColoredVertex> vertices;

    unsigned vao, vbo;
    unsigned drawMode;

    float     rotation          = 0.f;
    glm::vec3 rotationDirection = glm::vec3(0.f, 0.f, 1.f);

    virtual const char *__name() = 0;

  public:
    // This will be called each loop by the engine.
    void draw(glm::mat4 projection, glm::mat4 view);

    // Use radians and rotate around the Z axis by default.
    void rotate(float radians);

    void setSize(glm::vec3 newSize);
    void setSize(glm::vec2 newSize);
    void setSize(int w, int h);

    glm::vec3 pos;
    glm::vec3 size;
};
}; // namespace pgl::drawable

// Included shapes.
#include <drawable/triangle.hpp>