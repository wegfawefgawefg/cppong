#pragma once

#ifndef ENTITY_H
#define ENTITY_H

class Game;
class Entity {
    public:
        int id;
        float x, y;
        float vx, vy;
        float width, height;

	Entity(float x, float y, float width, float height);
    ~Entity();
    void step(const Game&);
};

#endif