// SPDX-License-Identifier: LGPL-3.0-or-later

#include <glm/gtx/string_cast.hpp>

#include <drawable/cricle.hpp>

#include <util.hpp>

using namespace pgl::drawable;

Circle::Circle(glm::vec2 position, float radius) {
    debug("(%s) Creating drawable object at %s, of radius %.2f.",
          __name(),
          glm::to_string(position).c_str(),
          radius);

    vertices.push_back(Vertex(.5f, .5f));

    for (float i = 0.f; i <= 2 * M_PI; i += glm::radians(10.f)) {
        vertices.push_back(Vertex(cos(i) / 2 + .5f, sin(i) / 2 + .5f));
    }

    size(radius * 2, radius * 2);
    Drawable::pos(position);

    buffersReady();
    drawMode = GL_TRIANGLE_FAN;

    shader = new Shader();
    shader->addShader(Shader::spacial, Shader::vert);
    shader->addShader(Shader::simple, Shader::frag);
    shader->linkProgram();
}

Circle::Circle(int x, int y, float radius) : Circle({x, y}, radius) {
}