#include <iostream>

#include "game.hpp"
#include "graphics.hpp"

Graphics::Graphics() {
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 16);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
    SDL_GL_SetSwapInterval(0);

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    window = SDL_CreateWindow("cppong",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_width, window_height,
        SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderSetLogicalSize(renderer, width, height);

    SDL_ShowCursor(SDL_DISABLE);
    SDL_RaiseWindow(window);

    const int font_size = width / 20;
    font = TTF_OpenFont("./assets/font/FreeSans.ttf", font_size);
    if (font == NULL) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(1);
    }
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Graphics::draw_text(const char *text, const SDL_Color color, const int x, const int y) {
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect = {x, y, text_surface->w, text_surface->h};
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void Graphics::draw_frame_rate(float dt) {
    const double fps = 1.0 / dt; 
    const SDL_Color color = {255, 255, 255, 255};
    char fps_str[32];
    sprintf(fps_str, "%f", fps);
    draw_text(fps_str, color, 0, 0);
}


void Graphics::render(const Game& game){ 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_frame_rate(game.dt);
    SDL_RenderPresent(renderer);
}