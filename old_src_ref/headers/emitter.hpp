#pragma once

#ifndef EMITTER_H
#define EMITTER_H

class Game;
class Transient;
class Emitter : public Transient {
    public:

    Emitter(float x, float y, float width, float height, float vx, float vy, float lifespan);
    ~Emitter();
    void step(Game&);
    void set_inactive(Game& game);
};

#endif