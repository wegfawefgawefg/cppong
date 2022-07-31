#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

#include "sprite.hpp"

class Game;
class Entity {
public:
    int id;
    bool active = true; //  entities culled if this is false

    static constexpr float MAX_SPEED = 2000.0f;
    bool has_physics = true;

    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 acc;
    glm::vec2 size;

    ////    "transient" entities die after a while
    bool transient = false;
    float lifespan = 0.0;
    float age = 0.0;

    Sprite* sprite = NULL;

    Entity();
    Entity(glm::vec2 pos, glm::vec2 size);
    Entity(glm::vec2 pos, glm::vec2 size, glm::vec2 vel);
    virtual ~Entity();
    virtual void step(Game& game);
    virtual void step_physics(Game& game);
    void set_inactive();
    void set_transient(float lifespan);
    void disable_physics();
    void enable_physics();
    virtual void collide(Game& game, Entity* entity);
    void add_force(glm::vec2 force);
    glm::vec2 get_br();
    glm::vec2 get_center();
    bool intersects(Entity* b);
    void bounce_away_from(Entity* b);
    void bounce_away_from_position(glm::vec2 p);
    void set_sprite(Sprite* sprite);

    // friend bool operator< (const Entity& left, const Point2D& right);
};
#endif
