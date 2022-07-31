#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>

#include "sprite_resource.hpp"
#include "sprite.hpp"

class Game;
class Graphics
{
public:
    // static const int window_width = 1280;
    // static const int window_height = 720;

    glm::vec2 window_dims = glm::vec2(1280, 720);

    // glm::vec2 dims = glm::vec2(240, 160); // gba
    // glm::vec2 dims = glm::vec2(160, 144); // gb
    // glm::vec2 dims = window_dims; // native
    glm::vec2 dims = window_dims / 2.0f; // half native

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;

    std::vector<SpriteResource*> sprite_resources;

    Graphics();
    ~Graphics();

    void render(Game& game);

    //  drawing
    void draw_frame_rate(float dt);
    void draw_entity_count(int num_entities);
    void draw_scores(Game& game);
    void render_collision_flags(Game& game);

    glm::vec2 get_center();
    void load_sprite_resources();
    void add_sprite_resource(
        std::string path,
        int width, int height,
        std::vector<int> anims_num_frames,
        float frame_duration);

    //  primitives
    void draw_text(
        const char* text,
        const SDL_Color color,
        const int x, const int y);
    void draw_plane(glm::vec2 p, glm::vec2 dir);
    void draw_rect(glm::vec2 pos, glm::vec2 size);
    void draw_centered_rect(glm::vec2 pos, glm::vec2 size);
    void draw_line(glm::vec2 p1, glm::vec2 p2);
    void draw_sprite(Sprite* sprite, glm::vec2 pos);

};

#endif
