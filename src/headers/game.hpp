#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL.h>
#include "graphics.hpp"
#include "audio.hpp"
#include "sequencer.hpp"
#include "entity.hpp"
#include "grid.hpp"
#include "camera.hpp"

class Game {
public:
    Graphics* graphics = NULL;
    Audio* audio = NULL;
    Sequencer* sequencer = NULL;
    Camera* camera = NULL;

    bool running = false;
    Uint64 now;
    double dt;

    std::vector<Entity*> entities;
    Grid* grid = NULL;

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

    //  util
    glm::vec2 get_mouse_pos();

    // debug
    void initialize_grid_bounds_checking_entities();
    void initialize_collision_testing_entities();

};

#endif

