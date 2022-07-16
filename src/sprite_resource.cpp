#include <iostream>

#include "sprite_resource.hpp"

SpriteResource::SpriteResource(
    SDL_Renderer* renderer,
    std::string path,
    int width, int height,
    std::vector<int> anims_num_frames,
    float frame_duration
) {
    texture = IMG_LoadTexture(renderer, path.c_str());
    // check if texture loaded successfully
    if (texture == NULL) {
        printf("Failed to load texture: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_QueryTexture(texture, NULL, NULL, &base_width, &base_height);

    width = width;
    height = height;

    int longest_anim_length = 0;
    for (auto& an_anim_length : anims_num_frames) {
        if (an_anim_length > longest_anim_length) {
            longest_anim_length = an_anim_length;
        }
    }

    zone_width = base_width / longest_anim_length;
    zone_height = base_height / anims_num_frames.size();
    anims_num_frames = anims_num_frames;
    frame_duration = frame_duration;
}

SpriteResource::~SpriteResource() {}


