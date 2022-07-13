#include <iostream>
#include <random>

#include "game.hpp"
#include "entity.hpp"
#include "transient.hpp"

Transient::Transient( 
        float x, float y, float width, float height, 
        float vx, float vy, float lifespan) 
        : Entity(x, y, width, height, vx, vy) {
    this->lifespan = lifespan;
    this->age = 0;
}

Transient::~Transient() {
}

void Transient::step(Game& game){
    Entity::step(game);
    age += game.dt;
    if(age > lifespan){
        // active = false;
        Entity::set_inactive(game);
    }
}

