// SPDX-License-Identifier: LGPL-3.0-or-later

#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <drawable/triangle.hpp>

#include <util.hpp>

using namespace pgl::drawable;

Triangle::Triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3) {
    debug("(%s) Creating drawable object at %s, %s, %s",
          __name(),
          glm::to_string(p1).c_str(),
          glm::to_string(p2).c_str(),
          glm::to_string(p3).c_str());

    vertices.push_back(ColoredVertex(p1));
    vertices.push_back(ColoredVertex(p2));
    vertices.push_back(ColoredVertex(p3));

    normalizeVertices();

    buffersReady();
    drawMode = GL_TRIANGLES;

    shader = new Shader();
    shader->addShader(Shader::spacial, Shader::vert);
    shader->addShader(Shader::simple, Shader::frag);
    shader->linkProgram();
}

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
    : Triangle(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(x3, y3)) {
}