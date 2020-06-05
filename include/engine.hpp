// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include <camera.hpp>
#include <drawable.hpp>
#include <shader.hpp>

namespace pgl {
class Engine {
  public:
    Engine();
    ~Engine();

    float deltaTime;

    bool running();

    void initInternals(int w, int h);

    void background(int r, int g, int b);

    void update();
    void draw();
    void stop();
    void handleEvents();

  private:
    void checkSDL();
    void setup();
    void die(const std::string &message, bool _stop);

    SDL_Window *                      window;
    SDL_GLContext                     glContext;
    bool                              isRunning;
    unsigned                          width, height;
    float                             deltaCounter;
    Camera *                          camera;
    std::vector<drawable::Drawable *> sceneObjs;
};
} // namespace pgl