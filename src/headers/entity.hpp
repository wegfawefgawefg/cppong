#pragma once

#ifndef ENTITY_H
#define ENTITY_H

class Game;
class Entity {
    public:
        int id;
        bool active = true;
        float x, y;
        float vx, vy;
        float width, height;

    Entity();
	Entity(float x, float y, float width, float height);
    Entity(float x, float y, float width, float height, float vx, float vy);
    virtual ~Entity();
    virtual void step(Game&);
};

#endif