#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>

#include <SDL.h>
#include <glm/glm.hpp>

#include "sprite_resource.hpp"

class Sprite
{
public:
    SpriteResource* resource = NULL;

    int anim_index;
    int frame_index;
    float timer;
    float speed;
    glm::vec2 scale = glm::vec2(1.0, 1.0);

    Sprite(SpriteResource* resource);
    ~Sprite();

    void step(float dt);
    void rollover_to_begining_of_anim();

    void randomize_timer();
    void reset_speed();
    void set_speed(float speed);
    void set_anim_frame_index(int frame_index);
    void set_anim(int anim_index);
    void set_scale(glm::vec2 scale);
    void set_size(glm::vec2 size);
    void multiply_scale(glm::vec2 scale);
    // void draw(SDL_Renderer *renderer, int x, int y);
    // void print();

};

#endif
