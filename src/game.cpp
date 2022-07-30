#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "game.hpp"
#include "graphics.hpp"
#include "entity.hpp"
#include "random.hpp"
#include "utils.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "score_zone.hpp"
#include "test_entity.hpp"
#include "sequencer.hpp"

Game::Game() {
    this->graphics = new Graphics();
    this->audio = new Audio();
    this->sequencer = new Sequencer();
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

void Game::add_entity(Entity* e) {
    this->entities.push_back(e);
}

void Game::build_grid() {
    this->grid = new Grid(
        glm::vec2(0.0, 0.0),
        glm::vec2(graphics->width, graphics->height),
        20.0f
    );
    for (auto e : this->entities) {
        this->grid->insert_entity(e);
    }
}

void Game::process_collisions() {
    for (auto& entity : this->entities) {
        std::vector<Entity*> hits = this->grid->query(entity->pos, entity->get_br());
        for (Entity* against_entity : hits) {
            if (entity->id == against_entity->id) {
                continue;
            }
            if (entity->intersects(against_entity)) {
                entity->collide(*this, against_entity);
            }
        }
    }
}

void Game::setup_game() {
    build_grid();
    float paddle_width = graphics->width / 4.0;
    float paddle_height = graphics->height / 16.0;

    ////////////////    INIT PADDLES    ////////////////
    // //  enemy paddle
    // Paddle* enemy_paddle = new Paddle(
    //     glm::vec2(1, paddle_height / 2.0),
    //     glm::vec2(paddle_width, paddle_height),
    //     glm::vec2(100, 0)
    // );
    // add_entity(enemy_paddle);

    // //  player paddle
    // Entity* player_paddle = new Paddle(
    //     glm::vec2(0, graphics->height - paddle_height - paddle_height / 2.0),
    //     glm::vec2(paddle_width, paddle_height),
    //     glm::vec2(1000, 0)
    // );
    // add_entity(player_paddle);

    ////////////////    SCORE ZONES    ////////////////
    Entity* enemy_score_zone = new ScoreZone(
        glm::vec2(0.0, 0.0),
        glm::vec2(graphics->width, paddle_height / 2.0 - 2),
        0
    );
    enemy_score_zone->disable_physics();
    add_entity(enemy_score_zone);

    Entity* player_score_zone = new ScoreZone(
        glm::vec2(0, graphics->height - paddle_height / 2.0 + 2),
        glm::vec2(graphics->width, paddle_height / 2.0),
        1
    );
    player_score_zone->disable_physics();
    add_entity(player_score_zone);

}

void Game::initialize_collision_testing_entities() {
    glm::vec2 half = glm::vec2(graphics->width / 2.0, graphics->height / 2.0);
    TestEntity* t1 = new TestEntity(
        glm::vec2(half.x, half.y),
        glm::vec2(20, 20)
    );
    // t1->disable_physics();
    add_entity(t1);

    TestEntity* t2 = new TestEntity(
        glm::vec2(half.x + 21, half.y),
        glm::vec2(20, 20)
    );
    // t2->disable_physics();
    add_entity(t2);
}

void Game::initialize_grid_bounds_checking_entities() {
    Entity* test_entity = new Entity(
        glm::vec2(graphics->width / 2.0, graphics->height / 2.0),
        glm::vec2(10.0, 1.0),
        glm::vec2(0, 0)
    );
    test_entity->disable_physics();
    add_entity(test_entity);

    Entity* out_of_bounds_test_entity = new Entity(
        glm::vec2(graphics->width, graphics->height),
        glm::vec2(10.0, 1.0),
        glm::vec2(0, 0)
    );
    out_of_bounds_test_entity->disable_physics();
    add_entity(test_entity);

    Entity* tl_partially_out_of_bounds_test_entity = new Entity(
        glm::vec2(-10, -10),
        glm::vec2(100.0, 100.0),
        glm::vec2(0, 0)
    );
    tl_partially_out_of_bounds_test_entity->disable_physics();
    add_entity(tl_partially_out_of_bounds_test_entity);


    Entity* br_partially_out_of_bounds_test_entity = new Entity(
        glm::vec2(graphics->width - 50, graphics->height - 50),
        glm::vec2(100.0, 100.0),
        glm::vec2(0, 0)
    );
    br_partially_out_of_bounds_test_entity->disable_physics();
    add_entity(br_partially_out_of_bounds_test_entity);
}
glm::vec2 Game::get_mouse_pos() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(
        float(x) / this->graphics->window_width * this->graphics->width,
        float(y) / this->graphics->window_height * this->graphics->height
    );
}

void Game::process_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
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

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_Q]) {
        running = 0;
    }

    /*if mouse is clicked make a new entity at mouse position*/
    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        // float pan = x / float(graphics->width);
        // audio->sound_play_at(0, pan, 0.0);
        int particle_count = 1;
        glm::vec2 mouse = get_mouse_pos();
        for (int i = 0; i < particle_count; i++) {
            // const float maxvel = 200;

            Ball* new_entity = new Ball(
                mouse + glm::diskRand(10.0f) - glm::diskRand(10.0f),
                glm::vec2(5.0f, 5.0f),
                glm::circularRand(200.0f)
            );
            // float lifespan = frand(0.1, 2);
            // new_entity->set_transient(lifespan);
            entities.push_back(new_entity);
        }
    }
}

void Game::clear_inactive_entities() {
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

void Game::update() {
    Uint64 last = now;
    now = SDL_GetPerformanceCounter();
    this->dt = (double)((now - last) / (double)SDL_GetPerformanceFrequency());

    this->time_since_last_ball -= dt;
    if (this->time_since_last_ball <= 0) {
        Ball* new_entity = new Ball(
            glm::vec2(this->graphics->width / 2.0, this->graphics->height / 2.0),
            glm::vec2(5.0f, 5.0f),
            glm::diskRand(400.0)
        );
        entities.push_back(new_entity);
        this->time_since_last_ball = Game::TIME_BETWEEN_BALLS;
    }

    build_grid();
    process_collisions();
    clear_inactive_entities();
    for (auto& entity : entities) {
        entity->step(*this);
    }
    sequencer->step(*this);
}

void Game::render() {
    graphics->render(*this);
}
