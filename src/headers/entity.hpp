#pragma once

#ifndef ENTITY_H
#define ENTITY_H

class Game;
class Sprite;
class Entity {
    public:
        int id;
        bool active = true; //  entities culled if this is false

        bool has_physics = true;
        float x, y;
        float vx, vy;
        float width, height;
        
        ////    "transient" entities die after a while
        bool transient = false;
        float lifespan = 0.0;
        float age = 0.0;


        // Sprite& sprite;

    Entity();
	Entity(float x, float y, float width, float height);
    Entity(float x, float y, float width, float height, float vx, float vy);
    virtual ~Entity();
    virtual void step(Game&);
    void set_inactive(Game& game);
    void set_transient(float lifespan);
    void disable_physics();
    void enable_physics();
};

#endif