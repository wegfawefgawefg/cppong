#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>

#include <SDL2/SDL.h>

class SpriteResource{
    public:
        int base_width;
        int base_height;
        int width;
        int height;
        int zone_width;
        int zone_height;
        std::vector<int> anims_num_frames;
        float frame_duration;

    SpriteResource(
        SDL_Renderer *renderer, 
        std::string path,
        int width, int height,
        int num_anims, 
        std::vector<int> anims_num_frames,
        float frame_duration);
    ~SpriteResource();
}

class Sprite{
    public:
        SpriteResource& resource;
        int anim_index;
        int frame_index;
        float timer;
        float speed;

    Sprite(SpriteResource& resource);
    ~Sprite();
    void step(float dt);
    void randomize_timer();
    void reset_speed();
    void set_speed(float speed);
    void set_anim_frame_index(int frame_index);
    void set_anim(int anim_index);
    void draw

#endif