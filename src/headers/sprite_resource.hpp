#pragma once

#ifndef SPRITE_RESOURCE_H
#define SPRITE_RESOURCE_H

#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

class SpriteResource
{
public:
    SDL_Texture* texture = nullptr;
    int base_width = 0;
    int base_height = 0;
    int width = 0;
    int height = 0;
    int zone_width = 0;
    int zone_height = 0;
    std::vector<int> anims_num_frames;
    float frame_duration;

    SpriteResource(
        SDL_Renderer* renderer,
        std::string path,
        int width, int height,
        std::vector<int> anims_num_frames,
        float frame_duration);
    ~SpriteResource();

    int get_num_anims();
};

#endif
