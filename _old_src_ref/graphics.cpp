#include <iostream>

#include "game.hpp"
#include "graphics.hpp"
#include "sprite_resource.hpp"

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

    // SDL_ShowCursor(SDL_DISABLE);
    SDL_RaiseWindow(window);

    const int font_size = width / 20;
    font = TTF_OpenFont("./assets/font/FreeSans.ttf", font_size);
    if (font == NULL) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(1);
    }

    load_sprite_resources(this);
}

Graphics::~Graphics() {
    std::cout << "Graphics destroyed" << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
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

void Graphics::draw_entity_count(int num_entities) {
    const SDL_Color color = {150, 255, 255, 255};
    char str[32];
    sprintf(str, "%d", num_entities);
    draw_text(str, color, 0, 400);
}

void Graphics::render(const Game& game){ 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    // render all the entities here
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (auto& entity : game.entities) {
        SDL_Rect rect = {
            int(entity->x - entity->width/2), 
            int(entity->y - entity->height/2), 
            int(entity->width), 
            int(entity->height)};
        SDL_RenderFillRect(renderer, &rect);
    }

    draw_frame_rate(game.dt);
    draw_entity_count(game.entities.size());
    SDL_RenderPresent(renderer);
}

void Graphics::load_sprite_resources(
    Graphics* graphics
){
    // // load in human sprite
    // int human_sprite_num_anims = 4;
    // int * human_sprite_anim_lengths = malloc(sizeof(int) * 4);
    // human_sprite_anim_lengths[0] = 4;
    // human_sprite_anim_lengths[1] = 4;
    // human_sprite_anim_lengths[2] = 4;
    // human_sprite_anim_lengths[3] = 4;
    // struct Sprite_resource *human_sprite_resource = sprite_resource_new(
    //     game->renderer, 
    //     "assets/images/Minifantasy_Dungeon_Assets/Animations/Human/Minifantasy_CreaturesHumanBaseWalk.png"
    //     128, 128, human_sprite_num_anims, human_sprite_anim_lengths, 0.2);

    SpriteResource reticle_sprite_resource = SpriteResource(
        graphics->renderer, 
        "assets/images/crosshair025.png",
        64, 64, 
        std::vector<int>{1}, 
        0.2);

    graphics->sprite_resources.push_back(reticle_sprite_resource);
}
