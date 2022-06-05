#include <iostream>

#include "Graphics.hpp"

Graphics::Graphics()
{
    window = nullptr;
    renderer = nullptr;
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

bool Graphics::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(window = SDL_CreateWindow(title, xpos, ypos, width, height, flags)))
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(renderer = SDL_CreateRenderer(window, -1, 0)))
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() != 0)
    {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return false;
    }

    if (!(font = TTF_OpenFont("assets/OneSlot.ttf", 24)))
    {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    return true;
}

void Graphics::setWindowTitle(const char* text)
{
    SDL_SetWindowTitle(window, text);
}

void Graphics::drawText(const char* text, const SDL_Color color, const int x, const int y)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, color);
    if (!text_surface)
    {
        std::cout << "Error: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect = { x, y, text_surface->w, text_surface->h };
    render(text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}


glm::vec2 Graphics::getWindowSize()
{
    std::vector<int> window_size;
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    return glm::vec2(width, height);
}

void Graphics::clear()
{
    SDL_SetRenderDrawColor(renderer, 60, 50, 60, 255);
    SDL_RenderClear(renderer);
}

void Graphics::render(SDL_Texture* texture)
{
    render(texture, NULL, NULL);
}

void Graphics::render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect)
{
    SDL_RenderCopy(renderer, texture, srcRect, destRect);
}

void Graphics::renderRect(SDL_Rect* rect, const SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, rect);
}

void Graphics::renderText(std::string text, SDL_Color color, glm::vec2* position)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!text_surface)
    {
        std::cout << "Error: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect = { (int)position->x, (int)position->y, (int)text_surface->w, (int)text_surface->h };
    render(text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void Graphics::present()
{
    SDL_RenderPresent(renderer);
}