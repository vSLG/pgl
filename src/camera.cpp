#include <glm/gtc/matrix_transform.hpp>

#include <camera.hpp>

using namespace pgl;

Camera::Camera(glm::vec2 resolution, glm::vec3 position, glm::vec3 upWorld) {
    pos     = position;
    worldUp = upWorld;
    target  = glm::vec3(0.0f, 0.0f, 0.0f);
    front   = glm::normalize(pos - target);
    right   = glm::normalize(glm::cross(worldUp, front));
    up      = glm::cross(front, right);

    projection = glm::perspective(glm::radians(45.0f), resolution[0] / resolution[1], 0.1f, 100.0f);
}

glm::mat4 Camera::view() {
    return glm::lookAt(pos, target, up);
}