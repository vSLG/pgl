// SPDX-License-Identifier: LGPL-3.0-or-later

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include <drawable.hpp>
#include <util.hpp>

using namespace pgl::drawable;

// Must call update() manually!
Drawable::Drawable() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}

Drawable::~Drawable() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    delete shader;
}

void Drawable::update() {
    model = glm::mat4(1.f);

    // Always scale, rotate and translate in this order (read order is reverse).
    model = glm::translate(model, pos_);
    model = glm::rotate(model, rotation, rotationDirection);
    model = glm::scale(model, size_);
}

// This function should be called after setting the vertices vector.
void Drawable::buffersReady() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Load vertices + colors to buffer.
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(ColoredVertex),
                 &vertices[0],
                 GL_STATIC_DRAW);

    /* Now tell OpenGL how to get vertex position.
     * Index: 0;
     * Size: 3 (x, y, z);
     * Type: float;
     * Normalize: false;
     * Stride: sizeof(ColoredVertex) (how many steps to get to another vertex
     * data);
     * Pointer: 0.
     */
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), (void *) 0);

    glEnableVertexAttribArray(0); // (layout = 0) in the vertex shader.

    // Same as above, but now for colors.
    glVertexAttribPointer(1,
                          4,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(ColoredVertex),
                          (void *) (3 * sizeof(float)));

    glEnableVertexAttribArray(1); // (layout = 1) in the vertex shader.
}

// Transform shape in vertices vector to a (0, 0) → (1, 1) space.
void Drawable::normalizeVertices() {
    ColoredVertex min = vertices.front();
    ColoredVertex max = vertices.front();

    for (ColoredVertex v : vertices) {
        if (v.x > max.x)
            max.x = v.x;
        else if (v.x < min.x)
            min.x = v.x;
        if (v.y > max.y)
            max.y = v.y;
        else if (v.y < min.y)
            min.y = v.y;
    }

    for (unsigned long i = 0; i < vertices.size(); i++) {
        vertices[i].x -= min.x;
        vertices[i].x /= max.x - min.x;
        vertices[i].y -= min.y;
        vertices[i].y /= max.y - min.y;
    }

    pos_ = {min.x, min.y, 0.f};
    size(max.x - min.x, max.y - min.y);
}

void Drawable::draw(glm::mat4 projection, glm::mat4 view) {
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);

    glBindVertexArray(vao);
    glDrawArrays(drawMode, 0, vertices.size());
}

void Drawable::rotate(float radians) {
    rotation = radians;
    update();
}

void Drawable::size(glm::vec3 newSize) {
    size_ = newSize;
    update();
}

void Drawable::size(glm::vec2 newSize) {
    size(glm::vec3(newSize, size_.z));
}

void Drawable::size(int w, int h) {
    size(glm::vec3(w, h, size_.z));
}

glm::vec3 Drawable::size() {
    return size_;
}

void Drawable::pos(glm::vec3 newPos) {
    pos_ = newPos;
    update();
}

void Drawable::pos(glm::vec2 newPos) {
    pos(glm::vec3(newPos, pos_.z));
}

void Drawable::pos(int x, int y) {
    pos(glm::vec3(x, y, pos_.z));
}

glm::vec3 Drawable::pos() {
    return pos_;
}