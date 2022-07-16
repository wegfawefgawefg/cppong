#include <iostream>
#include <random>

#include "game.hpp"

Entity::Entity() {
    id = rand();
    active = true;
}

Entity::Entity(glm::vec2 pos, glm::vec2 size) : Entity() {
    this->pos = pos;
    this->size = size;
    this->vel = glm::vec2(0.0, 0.0);
}

Entity::Entity(glm::vec2 pos, glm::vec2 size, glm::vec2 vel) : Entity(pos, size) {
    this->vel = vel;
}

Entity::~Entity() {}

void Entity::step(Game& game) {
    if (this->has_physics) {
        pos += +vel * float(game.dt);
        // vel *= 0.99;
        // const float gravity = 100.0;
        // vel.y += gravity * game.dt;

        // bounce of walls experimentally
        const float width = game.graphics->window_width;
        const float height = game.graphics->window_height;

        // // bouncing
        if (pos.x < 0) {
            pos.x = 0;
            vel.x *= -1;
        }
        else if (pos.x > width) {
            pos.x = width;
            vel.x *= -1;
        }

        if (pos.y < 0) {
            pos.y = 0;
            vel.y *= -1;
        }
        else if (pos.y > height) {
            pos.y = height;
            vel.y *= -1;
        }
    }

    // dissapear if out of bounds
    if (pos.x < 0 || pos.x > game.graphics->width || pos.y < 0 || pos.y > game.graphics->height) {
        active = false;
    }

    if (this->transient) {
        age += game.dt;
        if (age > lifespan) {
            Entity::set_inactive(game);
        }
    }
}

void Entity::set_inactive(Game& game) {
    active = false;
}

void Entity::set_transient(float lifespan) {
    this->transient = true;
    this->lifespan = lifespan;
}

void Entity::enable_physics() {
    this->has_physics = true;
}

void Entity::disable_physics() {
    this->has_physics = true;
}

glm::vec2 Entity::get_br() {
    return this->pos + this->size;
}
