#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Game;
class SpriteResource;
class Graphics {
    public:
        static const int window_width = 1280;
        static const int window_height = 720;

        static const int width = 1280;
        static const int height = 720;

        SDL_Window *window;
        SDL_Renderer *renderer;
        TTF_Font *font; 

        std::vector<SpriteResource> sprite_resources;

	Graphics();
    ~Graphics();
    void draw_text(        
        const char *text,
        const SDL_Color color, 
        const int x, const int y);
    void draw_frame_rate(float dt);
    void draw_entity_count(int num_entities);
    void render(const Game& game);
    void load_sprite_resources(Graphics* graphics);
};

#endif