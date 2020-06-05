// SPDX-License-Identifier: LGPL-3.0-or-later

#include <glm/gtc/matrix_transform.hpp>

#include <drawable.hpp>
#include <util.hpp>

using namespace pgl::drawable;

Drawable::Drawable(glm::vec3 position, glm::vec3 shapeSize)
    : pos(position), size(shapeSize) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    update();
}

Drawable::Drawable(glm::vec2 position, glm::vec2 shapeSize)
    : Drawable(glm::vec3(position, 0.f), glm::vec3(shapeSize, 0.f)) {
}

Drawable::Drawable(int x, int y, int w, int h)
    : Drawable(glm::vec3(x, y, 0.f), glm::vec3(w, h, 0.f)) {
}

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
    model = glm::translate(model, pos);
    model = glm::rotate(model, rotation, rotationDirection);
    model = glm::scale(model, size);
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

    pos = {min.x, min.y, 0.f};
    setSize(max.x - min.x, max.y - min.y);
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

void Drawable::setSize(glm::vec3 newSize) {
    size = newSize;
    update();
}

void Drawable::setSize(glm::vec2 newSize) {
    setSize(glm::vec3(newSize, 0.f));
}

void Drawable::setSize(int w, int h) {
    setSize(glm::vec3(w, h, 0.f));
}