#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <shader.hpp>

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
    void loadAllShaders(const std::string &dir);
    void setup();
    void die(const std::string &message);

    SDL_Window *          window;
    SDL_GLContext         glContext;
    bool                  isRunning;
    unsigned              _frameCount;
    std::vector<Shader *> shaders;

    unsigned vbo, vao;
};