#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

class Game;
class Sprite;
class Entity {
public:
    int id;
    bool active = true; //  entities culled if this is false

    bool has_physics = true;

    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 size;

    ////    "transient" entities die after a while
    bool transient = false;
    float lifespan = 0.0;
    float age = 0.0;

    // Sprite& sprite;

    Entity();
    Entity(glm::vec2 pos, glm::vec2 size);
    Entity(glm::vec2 pos, glm::vec2 size, glm::vec2 vel);
    virtual ~Entity();
    virtual void step(Game&);
    void set_inactive(Game& game);
    void set_transient(float lifespan);
    void disable_physics();
    void enable_physics();
};

#endif