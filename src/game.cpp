#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "game.hpp"
#include "graphics.hpp"
#include "entity.hpp"
#include "random.hpp"
#include "utils.hpp"

Game::Game() {
    graphics = new Graphics();
    audio = new Audio();
}

Game::~Game() {
    delete graphics;
    delete audio;
    SDL_Quit();
}

void Game::run() {
    std::cout << "Game running" << std::endl;
    running = true;
    now = SDL_GetPerformanceCounter();

    setup_game();
    while (running) {
        process_events();
        update();
        render();
    }
}

void Game::setup_game() {
    this->grid = new Grid(
        glm::vec2(0.0, 0.0),
        glm::vec2(graphics->width, graphics->height),
        500.0f
    );
    float paddle_width = graphics->width / 4.0;
    float paddle_height = graphics->height / 16.0;

    ////////////////    INIT PADDLES    ////////////////
    //  enemy paddle
    Entity *enemy_paddle = new Entity(
        glm::vec2(paddle_width, paddle_height), 
        glm::vec2(paddle_width, paddle_height), 
        glm::vec2(100, 0)
    );
    entities.push_back(enemy_paddle);

    //  player paddle
    Entity *player_paddle = new Entity(
        glm::vec2(paddle_width, graphics->height-paddle_height + 1), 
        glm::vec2(paddle_width, paddle_height), 
        glm::vec2(1000, 0)
    );
    entities.push_back(player_paddle);

    ////////////////    SCORE ZONES    ////////////////
    Entity *enemy_score_zone = new Entity(
        glm::vec2(graphics->width / 2.0, paddle_height / 4.0), 
        glm::vec2(graphics->width, paddle_height / 2.0), 
        glm::vec2(0, 0)
    );
    enemy_score_zone->disable_physics();
    entities.push_back(enemy_score_zone);

    Entity *player_score_zone = new Entity(
        glm::vec2(graphics->width / 2.0, graphics->height - paddle_height / 4.0 + 1), 
        glm::vec2(graphics->width, paddle_height / 2.0), 
        glm::vec2(0, 0)
    );
    player_score_zone->disable_physics();
    entities.push_back(player_score_zone);
}

void Game::process_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        running = 0;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = 0;
                break;
        }
    }

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_Q]) {
        running = 0;
    } 

    /*if mouse is clicked make a new entity at mouse position*/
    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        float pan = x / float(graphics->width);
        audio->sound_play_at(0, pan, 0.0);
        int particle_count = 10;
        for(int i = 0; i < particle_count; i++) {
            const float maxvel = 200;
            Entity *new_entity = new Entity(
                glm::vec2(float(x), float(y)), 
                glm::vec2(frand(1, 5), frand(1, 5)),
                glm::diskRand(maxvel)
            );
            float lifespan = frand(0.1, 2);
            new_entity->set_transient(lifespan);
            entities.push_back(new_entity);
        }
    }
}

void Game::update() {
    Uint64 last = now;
    now = SDL_GetPerformanceCounter();
    dt = (double)((now - last) / (double)SDL_GetPerformanceFrequency());

    for (auto& entity : entities) {
        entity->step(*this);
    }

    // make a new vector for the entities that are still active
    std::vector<Entity*> dead_entities;
    for (auto& entity : entities) {
        if (!entity->active) {
            dead_entities.push_back(entity);
        }
    }
    entities.erase(std::remove_if(entities.begin(), entities.end(), [](Entity* entity) {
            return !entity->active;
        }), entities.end());
    // delete the dead entities
    for (auto& entity : dead_entities) {
        delete entity;
    }
}

void Game::render() {
    graphics->render(*this); 
}
