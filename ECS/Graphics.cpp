//
// Created by Kyle Dougan on 6/6/22.
//

#include <iostream>

#include "Graphics.h"


Graphics::Graphics(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("SDL could not initialize!");
    }

    // Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth,
                              screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Window could not be created!");
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Renderer could not be created!");
    }

    // Init Font
    if (TTF_Init() < 0)
    {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
        throw std::runtime_error("TTF_Init: " + std::string(TTF_GetError()));
    }

    // Create Font

    font = TTF_OpenFont((fontPath + "square-pixel7.regular.ttf").c_str(), 24);
    if (font == nullptr)
    {
        std::cout << "Font could not be created! SDL_Error: " << TTF_GetError() << std::endl;
        throw std::runtime_error("Font could not be created!");
    }
}


Graphics::~Graphics()
{
    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Close font
    TTF_CloseFont(font);

    // Quit SDL subsystems
    SDL_Quit();
}


int Graphics::getScreenWidth() const
{
    return screenWidth;
}


int Graphics::getScreenHeight() const
{
    return screenHeight;
}


void Graphics::clear()
{
    SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    SDL_RenderClear(renderer);
}


void Graphics::present()
{
    SDL_RenderPresent(renderer);
}


void Graphics::drawRect(Position position, Volume volume, SDL_Color color)
{
    int x = (int) position.x;
    int y = (int) position.y;
    int w = (int) volume.x;
    int h = (int) volume.y;
    drawRect(x, y, w, h, color);
}

void Graphics::drawRect(int x, int y, int w, int h, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}


void Graphics::drawText(const char *text, int x, int y, SDL_Color color)
{
    drawText(text, x, y, color, Align::TOP_LEFT);
}

void Graphics::drawText(const Text &text, const Position position)
{
    drawText(text.value.c_str(), static_cast<int>(position.x), static_cast<int>(position.y), text.color,
             text.align);
}

void Graphics::drawText(const char *text, int x, int y, SDL_Color color, Align align)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    int textWidth = surface->w;
    int textHeight = surface->h;
    std::vector<int> offsets = getAlignOffsets(align, textWidth, textHeight);
    SDL_Rect rect = {x + offsets[0], y + offsets[1], textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}
