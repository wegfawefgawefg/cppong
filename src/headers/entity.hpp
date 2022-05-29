#pragma once

#ifndef ENTITY_H
#define ENTITY_H

class Game;
class Sprite;
class Entity {
    public:
        int id;
        bool active = true;
        float x, y;
        float vx, vy;
        float width, height;
        // Sprite& sprite;

    Entity();
	Entity(float x, float y, float width, float height);
    Entity(float x, float y, float width, float height, float vx, float vy);
    virtual ~Entity();
    virtual void step(Game&);
    void set_inactive(Game& game);
};

#endif