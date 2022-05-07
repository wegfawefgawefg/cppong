#include <iostream>
#include <random>

#include "game.hpp"

Entity::Entity(){
    id = rand();
    active = true;
}

Entity::Entity( float x, float y, float width, float height) : Entity(){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    const int speed = 1000;
    vx = rand() % speed - speed / 2;
    vy = rand() % speed - speed / 2;
}

Entity::Entity( float x, float y, float width, float height, float vx, float vy): Entity(x, y, width, height){
    this->vx = vx;
    this->vy = vy;
}

Entity::~Entity() {
}

void Entity::step(Game& game){ 
    x += vx * game.dt;
    y += vy * game.dt;

    // bounce of walls experimentally
    const float width = game.graphics->window_width;
    const float height = game.graphics->window_height;

    // // bouncing
    if( x < 0){
        x = 0;
        vx *= -1;
    } else if (x > width){
        x = width;
        vx *= -1;
    }

    if( y < 0){
        y = 0;
        vy *= -1;
    } else if (y > height){
        y = height;
        vy *= -1;
    }

    // dissapear if out of bounds
    // if( x < 0 || x > width || y < 0 || y > height){
    //     active = false;
    // }
}
