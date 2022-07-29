#pragma once

#ifndef BALL_H
#define BALL_H

#include <glm/glm.hpp>
#include <entity.hpp>

class Game;
class Sprite;
class Ball : public Entity {
public:
    float MAX_SPEED = 100.0f;
    Ball();
    Ball(glm::vec2 pos, glm::vec2 size);
    Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 vel);
    virtual ~Ball();
    virtual void step(Game& game);
    void collide(Game& game, Entity* entity);
};
#endif