#pragma once

#ifndef PADDLE_H
#define PADDLE_H

#include <glm/glm.hpp>
#include <entity.hpp>

class Game;
class Sprite;
class Paddle : public Entity {
public:
    glm::vec2 target;

    Paddle();
    Paddle(glm::vec2 pos, glm::vec2 size);
    Paddle(glm::vec2 pos, glm::vec2 size, glm::vec2 vel);
    virtual ~Paddle();
    virtual void step(Game& game);
    void collide(Game& game, Entity* entity) override;
};
#endif