#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>

#include <SDL.h>

class SpriteResource;

class Sprite
{
public:
    SpriteResource* resource;

    int anim_index;
    int frame_index;
    float timer;
    float speed;

    Sprite(SpriteResource* resource);
    ~Sprite();

    void step(float dt);
    void rollover_to_begining_of_anim();

    void randomize_timer();
    void reset_speed();
    void set_speed(float speed);
    void set_anim_frame_index(int frame_index);
    void set_anim(int anim_index);
    // void draw(SDL_Renderer *renderer, int x, int y);
    // void print();

};

#endif
