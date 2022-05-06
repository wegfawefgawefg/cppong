#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include "graphics.hpp"

class Game {
    public:
        Graphics* graphics;

        bool running = false;
        Uint64 now;
        double dt;

	Game();
    ~Game();
    void run();
    void process_events();
    void update();
    void render();
};

#endif