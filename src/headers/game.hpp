#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "entity.hpp"

class Game {
    public:
        Graphics* graphics;

        bool running = false;
        Uint64 now;
        double dt;

        std::vector<Entity*> entities;

	Game();
    ~Game();
    void run();
    void process_events();
    void update();
    void render();
};

#endif