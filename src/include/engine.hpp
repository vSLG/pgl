#pragma once

#include <SDL2/SDL.h>

class Engine {
  public:
    Engine();
    ~Engine();

    bool running() {
        return isRunning;
    }

    unsigned int frameCount() {
        return _frameCount;
    }

    void initInternals(int w, int h);

    void background(int r, int g, int b);

    void update();
    void draw();
    void stop();
    void handleEvents();

  private:
    void          checkSDL();
    SDL_Window *  window;
    SDL_Renderer *renderer;
    bool          isRunning   = false;
    unsigned int  _frameCount = 0;
};