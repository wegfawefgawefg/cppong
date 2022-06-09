//
// Created by Kyle Dougan on 6/6/22.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Utilities.h"


class Graphics
{
public:
    Graphics(int screenWidth, int screenHeight);

    ~Graphics();

    void clear();

    void present();

    [[nodiscard]] int getScreenWidth() const;

    [[nodiscard]] int getScreenHeight() const;

    void drawRect(int x, int y, int w, int h, SDL_Color color);

    void drawText(const char *text, int x, int y, SDL_Color color);

    void drawText(const char *text, int x, int y, SDL_Color color, Align align);

private:
    int screenWidth;
    int screenHeight;

    std::string fontPath = "assets/fonts/";

    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;

    SDL_Color clearColor = {10, 10, 20, 255};
};
