// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace pgl {

// This class is used to manipulate view space on the OpenGL viewport. It
// responds to keyboard and mouse events.
class Camera {
  public:
    Camera(glm::vec2 resolution,
           glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 upWorld  = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view();

    // Callbacks for user events.
    void mouseMotion(SDL_MouseMotionEvent *e);
    void keyboardInput(const uint8_t *e, float deltaTime);

    // Euler angles, used to calculate the direction of the camera.
    float yaw;
    float pitch;

    // Defined camera options.
    float sensitivity;
    float speed;
    float zoom;

    glm::vec3 pos;
    glm::mat4 projection; // Can be either perspective or orthogonal.

    // Camera axis
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    // Needed for calculating the camera axis.
    glm::vec3 worldUp;

  private:
    // Used to update camera vectors based on Euler angles and position. It must
    // be called whenever one of those or both changes.
    void update();
};
}; // namespace pgl