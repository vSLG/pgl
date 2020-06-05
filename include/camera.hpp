// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace pgl {

// This class is used to manipulate view space on the OpenGL viewport. It
// responds to keyboard and mouse events.
class Camera {
  public:
    enum Projection { PROJECTION_PERSPECTIVE, PROJECTION_ORTHOGRAPHIC };

    Camera(int       width,
           int       height,
           glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 upWorld  = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view();
    glm::mat4 projection();
    void      projection(Projection proj);
    void      setResolution(int width, int height);

    // Callbacks for user events.
    void mouseMotion(SDL_MouseMotionEvent *e);
    void keyboardInput(const uint8_t *e, float deltaTime);
    void toggleProjection();

    // Euler angles, used to calculate the direction of the camera.
    float yaw;
    float pitch;

    // Defined camera options.
    float sensitivity;
    float speed;
    float fov;

    glm::vec3 pos;

    // Camera axis
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    // Needed for calculating the camera axis.
    glm::vec3 worldUp;

  private:
    int        w, h;
    Projection currentProjection;
    glm::mat4  projection_; // Can be either perspective or orthogonal.

    // Used to update camera vectors based on Euler angles and position. It must
    // be called whenever one of those or both changes.
    void update();
};
}; // namespace pgl