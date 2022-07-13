#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>

#include <SDL2/SDL.h>

class SpriteResource;

class Sprite {
    public:
        Sprite(SpriteResource& resource);
        ~Sprite() = default;
        SpriteResource& resource;
        int anim_index;
        int frame_index;
        float timer;
        float speed;
    // void step(float dt);
    // void randomize_timer();
    // void reset_speed();
    // void set_speed(float speed);
    // void set_anim_frame_index(int frame_index);
    // void set_anim(int anim_index);
    // void draw(SDL_Renderer *renderer, int x, int y);
    // void print();
};

#endif
