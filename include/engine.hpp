#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include <camera.hpp>
#include <shader.hpp>

namespace pgl {
class Engine {
  public:
    Engine();
    ~Engine();

    bool running();

    unsigned frameCount();

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

    SDL_Window *  window;
    SDL_GLContext glContext;
    bool          isRunning;
    unsigned      _frameCount, width, height;
    Camera *      camera;
    Shader *      tempShader;
    unsigned      tempVao;
};
} // namespace pgl