#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>

class Game;
class SpriteResource;
class Graphics
{
public:
    static const int window_width = 1280;
    static const int window_height = 720;

    static const int width = 240;//160;//640;//1280;
    static const int height = 160;//144;//360;//720;

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    std::vector<SpriteResource> sprite_resources;

    Graphics();
    ~Graphics();
    void draw_text(
        const char* text,
        const SDL_Color color,
        const int x, const int y);
    void draw_frame_rate(float dt);
    void draw_entity_count(int num_entities);
    void draw_scores(Game& game);
    void render(Game& game);
    void load_sprite_resources(Graphics* graphics);
    void render_collision_flags(Game& game);
    glm::vec2 get_center();

    //  primitives
    void draw_plane(glm::vec2 p, glm::vec2 dir);
    void draw_rect(glm::vec2 pos, glm::vec2 size);
    void draw_centered_rect(glm::vec2 pos, glm::vec2 size);
    void draw_line(glm::vec2 p1, glm::vec2 p2);

};

#endif
