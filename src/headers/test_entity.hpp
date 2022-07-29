#pragma once

#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H

#include <glm/glm.hpp>
#include <entity.hpp>

class Game;
class Sprite;
class TestEntity : public Entity {
public:
    glm::vec2 target;

    TestEntity();
    TestEntity(glm::vec2 pos, glm::vec2 size);
    virtual ~TestEntity();
    virtual void step(Game& game);
    void collide(Game& game, Entity* entity);
};
#endif