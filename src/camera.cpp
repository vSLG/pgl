// SPDX-License-Identifier: LGPL-3.0-or-later

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

#include <camera.hpp>
#include <util.hpp>

using namespace pgl;

Camera::Camera(glm::vec2 resolution, glm::vec3 position, glm::vec3 upWorld)
    : // Initalize camera options with default predefined values.
      // TODO: make those optional.
      yaw(90.0f), pitch(0.0f), sensitivity(0.1f), speed(1.0f), zoom(75.0f) {
    debug("(Camera) Creating camera object");

    pos     = position;
    worldUp = upWorld;

    // Also let projection be optional.
    projection = glm::perspective(
        glm::radians(zoom), resolution[0] / resolution[1], 0.1f, 100.0f);

    // Start camera vectors since we just filled in with position and world up
    // vector.
    update();
}

glm::mat4 Camera::view() {
    // https://stackoverflow.com/a/21830455
    // http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
    return glm::lookAt(pos, front + pos, up);
}

void Camera::mouseMotion(SDL_MouseMotionEvent *e) {
    // Euler angles can be used to calculate the camera direction vector.
    yaw += e->xrel * sensitivity;
    pitch -= e->yrel * sensitivity;

    // Don't go above 90° or below -90°, else weird things will happen.
    pitch = std::clamp(pitch, -89.0f, 89.0f);

    update();
}

void Camera::keyboardInput(const uint8_t *e, float deltaTime) {
    glm::vec3 result(0.0f);

    // Check manually which key is pressed and add it to the result motion
    // vector.
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

    // Delta time must be used here, else the camera will move differently on
    // other devices. Delta time makes movement uniform on every platform.
    pos += result * speed * deltaTime;
}

void Camera::update() {
    // https://en.wikipedia.org/wiki/Euler_angles#Conversion_to_other_orientation_representations
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front   = glm::normalize(front);
    right   = glm::normalize(glm::cross(front, worldUp));
    up      = glm::normalize(glm::cross(right, front));
}