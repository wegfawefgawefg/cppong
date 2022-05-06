#include <iostream>

#include "game.hpp"

Entity::Entity( float x, float y, float width, float height) {
    id = rand();
    x = x;
    y = y;
    vx = 0;
    vy = 0;
    width = width;
    height = height;
}

Entity::~Entity() {
}

void Entity::step(const Game& game){ 
    x += vx * game.dt;
    y += vy * game.dt;

    // bounce of walls experimentally
}
