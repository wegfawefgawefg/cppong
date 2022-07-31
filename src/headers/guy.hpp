#pragma once

#ifndef GUY_H
#define GUY_H

#include <glm/glm.hpp>
#include <entity.hpp>

class Game;
class Sprite;
class Guy : public Entity {
public:
    float MAX_SPEED = 100.0f;
    Guy();
    Guy(glm::vec2 pos);
    virtual ~Guy();
    virtual void step(Game& game);
    void collide(Game& game, Entity* entity);
};
#endif