#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "audio.hpp"
#include "entity.hpp"

class Game {
    public:
        Graphics* graphics;
        Audio* audio;

        bool running = false;
        Uint64 now;
        double dt;

        // std::vector<T>::size_type enemy_score_zone;
        // std::vector<T>::size_type player_score_zone;
        // std::vector<T>::size_type enemy_paddle;
        // std::vector<T>::size_type player_paddle;
        std::vector<Entity*> entities;

	Game();
    ~Game();
    void run();
    void setup_game();
    void process_events();
    void update();
    void render();
};

#endif