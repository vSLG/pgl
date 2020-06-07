// SPDX-License-Identifier: LGPL-3.0-or-later

#include <glm/gtx/string_cast.hpp>

#include <drawable/quad.hpp>

#include <util.hpp>

using namespace pgl::drawable;

Quad::Quad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4) {
    debug("(%s) Creating drawable object at %s, %s, %s, %s",
          __name(),
          glm::to_string(p1).c_str(),
          glm::to_string(p2).c_str(),
          glm::to_string(p3).c_str(),
          glm::to_string(p3).c_str());

    unsigned indices[] = {0, 1, 3, 1, 2, 3};

    glGenBuffers(1, &ebo);

    vertices.push_back(Vertex(p1));
    vertices.push_back(Vertex(p2));
    vertices.push_back(Vertex(p3));
    vertices.push_back(Vertex(p4));

    normalizeVertices();

    buffersReady();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    drawMode = GL_TRIANGLES;

    shader = new Shader();
    shader->addShader(Shader::spacial, Shader::vert);
    shader->addShader(Shader::simple, Shader::frag);
    shader->linkProgram();
}

Quad::Quad(float x1,
           float y1,
           float x2,
           float y2,
           float x3,
           float y3,
           float x4,
           float y4)
    : Quad({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}) {
}

Quad::~Quad() {
    glDeleteBuffers(1, &ebo);
}

void Quad::draw(glm::mat4 projection, glm::mat4 view) {
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);

    glBindVertexArray(vao);
    glDrawElements(drawMode, vertices.size() + 2, GL_UNSIGNED_INT, 0);
}