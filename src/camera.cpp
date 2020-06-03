#include <glm/gtc/matrix_transform.hpp>

#include <camera.hpp>

using namespace pgl;

Camera::Camera(glm::vec3 position, glm::vec3 upWorld) {
    pos     = position;
    worldUp = upWorld;
    target  = glm::vec3(0.0f, 0.0f, 0.0f);
    front   = glm::normalize(pos - target);
    right   = glm::normalize(glm::cross(worldUp, front));
    up      = glm::cross(front, right);
}

glm::mat4 Camera::view() {
    return glm::lookAt(pos, target, up);
}