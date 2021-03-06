#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL.h>
#include "graphics.hpp"
#include "audio.hpp"
#include "entity.hpp"
#include "grid.hpp"

class Game {
public:
    Graphics* graphics;
    Audio* audio;

    bool running = false;
    Uint64 now;
    double dt;

    std::vector<Entity*> entities;
    Grid* grid;

    int player_score = 0;
    int enemy_score = 0;

    static constexpr float TIME_BETWEEN_BALLS = 2.0f;
    float time_since_last_ball = TIME_BETWEEN_BALLS;

    Game();
    ~Game();
    void run();
    void setup_game();
    void process_events();
    void update();
    void render();

    void clear_inactive_entities();
    void build_grid();
    void add_entity(Entity* e);
    void process_collisions();
    // void remove_entity()

    // debug
    void initialize_grid_bounds_checking_entities();


};

#endif

