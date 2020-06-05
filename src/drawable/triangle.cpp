// SPDX-License-Identifier: LGPL-3.0-or-later

#include <drawable/triangle.hpp>

#include <util.hpp>

using namespace pgl::drawable;

Triangle::Triangle(glm::vec3 position, glm::vec3 shapeSize)
    : Drawable(position, shapeSize) {
    debug("(%s) Creating drawable object at (%.2f, %.2f, %.2f).",
          __name(),
          pos[0],
          pos[1],
          pos[2]);

    // Simple equilateral triangle for now
    vertices.push_back(ColoredVertex(0.5f, -0.5f, 0.f, 1.f));
    vertices.push_back(ColoredVertex(-0.5f, -0.5f, 0.f, 0.f, 1.f));
    vertices.push_back(ColoredVertex(0.f, 0.5f, 0.f, 0.f, 0.f, 1.f));

    buffersReady();
    drawMode = GL_TRIANGLES;

    shader = new Shader();
    shader->addShader(Shader::spacial, Shader::vert);
    shader->addShader(Shader::simple, Shader::frag);
    shader->linkProgram();
}

Triangle::Triangle(glm::vec2 position, glm::vec2 shapeSize)
    : Triangle(glm::vec3(position, 0.f), glm::vec3(shapeSize, 0.f)) {
}

Triangle::Triangle(int x, int y, int w, int h)
    : Triangle(glm::vec3(x, y, 0.f), glm::vec3(w, h, 0.f)) {
}