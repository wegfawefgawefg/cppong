#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Game;
class Graphics {
    public:
        static const int window_width = 1280;
        static const int window_height = 720;

        static const int width = 1280;
        static const int height = 720;

        SDL_Window *window;
        SDL_Renderer *renderer;
        TTF_Font *font; 

	Graphics();
    ~Graphics();
    void draw_text(        
        const char *text,
        const SDL_Color color, 
        const int x, const int y);
    void draw_frame_rate(float dt);
    void render(const Game& game);
};

#endif