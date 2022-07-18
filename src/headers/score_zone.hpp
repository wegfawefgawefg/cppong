#pragma once

#ifndef SCORE_ZONE_H
#define SCORE_ZONE_H

#include <glm/glm.hpp>
#include <entity.hpp>

class Game;
class Sprite;
class ScoreZone : public Entity {
public:
    int team = 0;
    ScoreZone(glm::vec2 pos, glm::vec2 size, int team);
    virtual ~ScoreZone();
    virtual void step(Game& game);
    void collide(Game& game, Entity* entity, int direction);
};
#endif