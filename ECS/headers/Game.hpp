#pragma once

#include <SDL2/SDL.h>

class Graphics;
class Systems;
class Game
{
public:

    bool running;
    double deltaTime;
    float fps;

    Game();
    ~Game();

    void run();
    void handleEvents();
    void update();
    void render();

private:
    Graphics* graphics;
    Uint32 lastTime = 0;
    Systems* systems;
};