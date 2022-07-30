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
    this->acc = glm::vec2(0.0, 0.0);
}

Entity::Entity(glm::vec2 pos, glm::vec2 size, glm::vec2 vel) : Entity(pos, size) {
    this->vel = vel;
}

Entity::~Entity() {}

void Entity::bounce(Game* game, Entity* against) {

}

void Entity::step_physics(Game& game) {
    if (this->has_physics) {
        vel += acc * float(game.dt);
        this->vel.x = std::max(-Entity::MAX_SPEED, std::min(Entity::MAX_SPEED, this->vel.x));
        this->vel.y = std::max(-Entity::MAX_SPEED, std::min(Entity::MAX_SPEED, this->vel.y));
        pos += vel * float(game.dt);
    }
    this->acc = glm::vec2(0.0, 0.0);
}

void Entity::step(Game& game) {
    // // dissapear if out of bounds
    // if (pos.x < 0 || pos.x > game.graphics->width || pos.y < 0 || pos.y > game.graphics->height) {
    //     active = false;
    // }
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
glm::vec2 Entity::get_center() {
    return this->pos + this->size / 2.0f;
}


bool Entity::intersects(Entity* b) {
    glm::vec2 a_br = this->get_br();
    glm::vec2 b_br = b->get_br();

    if (a_br.x < b->pos.x || this->pos.x > b_br.x) { return false; }
    if (a_br.y < b->pos.y || this->pos.y > b_br.y) { return false; }
    return true;
}

/*
int Entity::sided_intersects(Entity* b) {
    glm::vec2 a_br = this->get_br();
    glm::vec2 b_br = b->get_br();

    float b_collision = b_br.y - this->pos.y;
    float t_collision = a_br.y - b->pos.y;
    float l_collision = a_br.x - b->pos.x;
    float r_collision = b_br.x - this->pos.x;

    if (    //  top collision
        t_collision < b_collision &&
        t_collision < l_collision &&
        t_collision < r_collision) {
        return 1;
    }
    if (    //  bottom collision
        b_collision < t_collision &&
        b_collision < l_collision &&
        b_collision < r_collision) {
        return 2;
    }
    if (    //  left collision
        l_collision < r_collision &&
        l_collision < t_collision &&
        l_collision < b_collision) {
        return 3;
    }
    if (    //  right collision
        r_collision < l_collision &&
        r_collision < t_collision &&
        r_collision < b_collision) {

        return 4;
    }

    return 0;
}
*/

void Entity::collide(Game& game, Entity* entity) {}

void Entity::bounce_away_from(Entity* b) {
    glm::vec2 b_c = b->get_center();
    this->bounce_away_from_position(b_c);
}

void Entity::bounce_away_from_position(glm::vec2 p) {
    float bounce_impulse = 40000.0;
    glm::vec2 a_c = this->get_center();
    glm::vec2 dif = a_c - p;
    this->acc += glm::normalize(dif) * bounce_impulse;
}
