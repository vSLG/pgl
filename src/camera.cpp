#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

#include <camera.hpp>

using namespace pgl;

Camera::Camera(glm::vec2 resolution, glm::vec3 position, glm::vec3 upWorld)
    : yaw(90.0f), pitch(0.0f), sensitivity(0.1f) {
    pos        = position;
    worldUp    = upWorld;
    projection = glm::perspective(
        glm::radians(45.0f), resolution[0] / resolution[1], 0.1f, 100.0f);

    update();
}

glm::mat4 Camera::view() {
    return glm::lookAt(pos, front, up);
}

void Camera::mouseMotion(SDL_MouseMotionEvent e) {
    yaw += e.xrel * sensitivity;
    pitch -= e.yrel * sensitivity;
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    update();
}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front   = glm::normalize(front);
    right   = glm::normalize(glm::cross(front, worldUp));
    up      = glm::normalize(glm::cross(right, front));
}