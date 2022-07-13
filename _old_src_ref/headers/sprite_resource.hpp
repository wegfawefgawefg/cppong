#pragma once

#ifndef SPRITE_RESOURCE_H
#define SPRITE_RESOURCE_H

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SpriteResource{
    public:
        SDL_Texture *texture;
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
        std::vector<int> anims_num_frames,
        float frame_duration);
    ~SpriteResource();
};

#endif