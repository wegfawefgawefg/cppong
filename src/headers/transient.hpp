#pragma once

#ifndef TRANSIENT_H
#define TRANSIENT_H

class Game;
class Entity;
class Transient : public Entity {
    public:
        float lifespan;
        float age;

    Transient(float x, float y, float width, float height, float vx, float vy, float lifespan);
    ~Transient();
    void step(Game&);
};

#endif