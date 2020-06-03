#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

#include <camera.hpp>

using namespace pgl;

Camera::Camera(glm::vec2 resolution, glm::vec3 position, glm::vec3 upWorld)
    : yaw(90.0f), pitch(0.0f), sensitivity(0.1f), speed(1.0f), zoom(75.0f) {
    pos        = position;
    worldUp    = upWorld;
    projection = glm::perspective(
        glm::radians(zoom), resolution[0] / resolution[1], 0.1f, 100.0f);

    update();
}

glm::mat4 Camera::view() {
    return glm::lookAt(pos, front + pos, up);
}

void Camera::mouseMotion(SDL_MouseMotionEvent *e) {
    yaw += e->xrel * sensitivity;
    pitch -= e->yrel * sensitivity;
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    update();
}

void Camera::keyboardInput(const uint8_t *e, float deltaTime) {
    glm::vec3 result(0.0f);
    if (e[SDL_SCANCODE_S] || e[SDL_SCANCODE_DOWN])
        result += glm::normalize(-front * glm::vec3(1., 0., 1.));
    if (e[SDL_SCANCODE_W] || e[SDL_SCANCODE_UP])
        result += glm::normalize(front * glm::vec3(1., 0., 1.));
    if (e[SDL_SCANCODE_A] || e[SDL_SCANCODE_LEFT])
        result += -right;
    if (e[SDL_SCANCODE_D] || e[SDL_SCANCODE_RIGHT])
        result += right;
    if (e[SDL_SCANCODE_LSHIFT])
        result += -glm::vec3(0., 1., 0.);
    if (e[SDL_SCANCODE_SPACE])
        result += glm::vec3(0., 1., 0.);

    pos += result * speed * deltaTime;
}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front   = glm::normalize(front);
    right   = glm::normalize(glm::cross(front, worldUp));
    up      = glm::normalize(glm::cross(right, front));
}