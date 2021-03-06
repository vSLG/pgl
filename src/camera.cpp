// SPDX-License-Identifier: LGPL-3.0-or-later

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

#include <camera.hpp>
#include <util.hpp>

using namespace pgl;

Camera::Camera(int width, int height, glm::vec3 position, glm::vec3 upWorld)
    : // Initalize camera options with default predefined values.
      yaw(-90.f), pitch(0.0f), sensitivity_(0.1f), speed_(100.f), fov_(45.0f),
      zoom_(1.f) {
    debug("(Camera) Creating camera object");

    pos     = position;
    worldUp = upWorld;
    w       = width;
    h       = height;

    projection(PROJECTION_ORTHOGRAPHIC);

    // Start camera vectors since we just filled in with position and world up
    // vector.
    update();
}

glm::mat4 Camera::view() {
    // https://stackoverflow.com/a/21830455
    // http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
    return glm::lookAt(pos, front + pos, up);
}

glm::mat4 Camera::projection() {
    return projection_;
}

void Camera::projection(Projection proj) {
    currentProjection = proj;

    switch (proj) {
        case PROJECTION_PERSPECTIVE:
            // Capture mouse inside the window.
            SDL_SetRelativeMouseMode(SDL_TRUE);
            projection_ = glm::perspective(glm::radians(fov() * (1 / zoom())),
                                           (float) w / (float) h,
                                           0.1f,
                                           1000.0f);
            break;
        case PROJECTION_ORTHOGRAPHIC:
            // Free mouse from the window.
            SDL_SetRelativeMouseMode(SDL_FALSE);
            projection_ = glm::ortho(-w * (1 / zoom()) / 2.f,
                                     w * (1 / zoom()) / 2.f,
                                     -h * (1 / zoom()) / 2.f,
                                     h * (1 / zoom()) / 2.f,
                                     0.f,
                                     1000.f);
            break;
    }
}

void Camera::setResolution(int width, int height) {
    w = width;
    h = height;

    projection(currentProjection);
}

void Camera::mouseMotion(SDL_MouseMotionEvent *e) {
    // Block mouse movement if in orthographic mode.
    if (currentProjection == PROJECTION_ORTHOGRAPHIC)
        return;

    // Euler angles can be used to calculate the camera direction vector.
    yaw += e->xrel * sensitivity();
    pitch -= e->yrel * sensitivity();

    // Don't go above 90° or below -90°, else weird things will happen.
    pitch = std::clamp(pitch, -89.9f, 89.9f);

    update();
}

void Camera::keyboardInput(const uint8_t *e, float deltaTime) {
    glm::vec3 result(0.0f);

    // Check manually which key is pressed and add it to the result motion
    // vector.
    if (e[SDL_SCANCODE_S] || e[SDL_SCANCODE_DOWN])
        result += currentProjection
                      ? -glm::vec3(0., 1., 0.)
                      : glm::normalize(-front * glm::vec3(1., 0., 1.));
    if (e[SDL_SCANCODE_W] || e[SDL_SCANCODE_UP])
        result += currentProjection
                      ? glm::vec3(0., 1., 0.)
                      : glm::normalize(front * glm::vec3(1., 0., 1.));
    if (e[SDL_SCANCODE_A] || e[SDL_SCANCODE_LEFT])
        result += -right;
    if (e[SDL_SCANCODE_D] || e[SDL_SCANCODE_RIGHT])
        result += right;
    if (e[SDL_SCANCODE_LSHIFT])
        result += -glm::vec3(0., 1., 0.);
    if (e[SDL_SCANCODE_SPACE])
        result += glm::vec3(0., 1., 0.);

    // Delta time must be used here, else the camera will move differently
    // on other devices. Delta time makes movement uniform on every
    // platform.
    pos += result * (speed() * (2.f / zoom())) * deltaTime;
}

void Camera::toggleProjection() {
    projection((Projection)((currentProjection + 1) % 2));
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

void Camera::addZoom(float quant) {
    zoom_ /= quant;
    projection(currentProjection);
}

void Camera::removeZoom(float quant) {
    zoom_ *= quant;
    zoom_ = zoom_ <= .3f ? .3f : zoom_;
    projection(currentProjection);
}

// Getters and setters

float Camera::zoom() {
    return zoom_;
}

void Camera::zoom(float zoom) {
    zoom_ = zoom;
}

float Camera::fov() {
    return fov_;
}

void Camera::fov(float fov) {
    fov_ = fov;
}

float Camera::speed() {
    return speed_;
}

void Camera::speed(float speed) {
    speed_ = speed;
}

float Camera::sensitivity() {
    return sensitivity_;
}

void Camera::sensitivity(float sensitivity) {
    sensitivity_ = sensitivity;
}