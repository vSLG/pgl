#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace pgl {
class Camera {
  public:
    Camera(glm::vec2 resolution,
           glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 upWorld  = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view();

    float yaw;
    float pitch;
    float sensitivity;

    glm::vec3 pos;
    glm::vec3 target;
    glm::mat4 projection;

    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    glm::vec3 worldUp;

    void mouseMotion(SDL_MouseMotionEvent e);

  private:
    void update();
};
}; // namespace pgl