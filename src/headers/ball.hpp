#pragma once

#ifndef BALL_H
#define BALL_H

#include <glm/glm.hpp>
#include <entity.hpp>

class Ball : public Entity {
public:
    Ball();
    Ball(glm::vec2 pos, glm::vec2 size);
    Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 vel);
    virtual ~Ball();
    virtual void step(Game&);
    void collide(Entity* entity);
};
#endif