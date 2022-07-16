#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL.h>
#include "graphics.hpp"
#include "audio.hpp"
#include "entity.hpp"
#include "grid.hpp"

class Game
{
    public:
        Graphics *graphics;
        Audio *audio;

        bool running = false;
        Uint64 now;
        double dt;

        std::vector<Entity*> entities;
        // Grid grid;

        Game();
        ~Game();
        void run();
        void setup_game();
        void process_events();
        void update();
        void render();
};

#endif
