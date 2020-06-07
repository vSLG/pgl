// SPDX-License-Identifier: LGPL-3.0-or-later

#include <glm/gtc/matrix_transform.hpp>

#include <drawable/polygon.hpp>

using namespace pgl::drawable;

// Calculate centroid by geometric decomposition. Not valid if polygon overlaps
// itself.
// https://en.wikipedia.org/wiki/Centroid#By_geometric_decomposition
glm::vec2 Polygon::centroid() {
    float polygonArea = 0.f;

    glm::vec2 centroidWeights(0.f);
    glm::vec2 v1 = vertices.front().xy();

    for (unsigned long i = 1; i < vertices.size() - 1; i++) {
        glm::vec2 vi  = vertices[i].xy() - v1;
        glm::vec2 vi1 = vertices[i + 1].xy() - v1;
        glm::vec2 ci  = v1 + (1.f / 3.f) * (vi + vi1);

        float wi = 0.5f * std::abs(glm::determinant(glm::mat2(vi, vi1)));

        polygonArea += wi;
        centroidWeights += ci * wi;
    }

    return glm::vec2(size_) * (centroidWeights / polygonArea);
}

void Polygon::update() {
    model = glm::mat4(1.f);

    // Transformations will not be affected if centered is false.
    centroid_ = centered() ? centroid() : glm::vec2(0.f);

    // Always scale, rotate and translate in this order (read order is reverse).
    model = glm::translate(model, pos());
    model = glm::rotate(model, rotation, rotationDirection);

    // Undo centroid translation (if any was made) for scaling correctly.
    model = glm::translate(model, -glm::vec3(centroid_, 0.f));
    model = glm::scale(model, size());
}

glm::vec3 Polygon::pos() {
    // Will not be affected if centroid is set to false.
    return pos_ + glm::vec3(centroid_, 0.f);
}

void Polygon::pos(glm::vec3 position) {
    pos_ = position - glm::vec3(centroid_, 0.f);
    update();
}

bool Polygon::centered() {
    return centered_;
}

void Polygon::centered(bool centered) {
    centered_ = centered;
    update();
}