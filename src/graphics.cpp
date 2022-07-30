#include <iostream>

// #include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/gtx/rotate_vector.hpp>

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

void Graphics::draw_text(const char* text, const SDL_Color color, const int x, const int y) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect = { x, y, text_surface->w, text_surface->h };
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void Graphics::draw_frame_rate(float dt) {
    const double fps = 1.0 / dt;
    const SDL_Color color = { 255, 255, 255, 255 };
    char fps_str[32];
    sprintf(fps_str, "%f", fps);
    draw_text(fps_str, color, 0, 0);
}

void Graphics::draw_entity_count(int num_entities) {
    const SDL_Color color = { 150, 255, 255, 255 };
    char str[32];
    sprintf(str, "%d", num_entities);
    draw_text(str, color, 0, 400);
}

glm::vec2 Graphics::get_center() {
    return glm::vec2(float(this->width), float(this->height)) / 2.0f;
}

void Graphics::render(Game& game) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    glm::vec2 cam_offset = game.camera->get_center() - this->get_center();

    // render grid here
    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 150);
    float start_x = game.grid->pos.x - cam_offset.x;
    float cell_size = game.grid->cell_size;
    glm::vec2 cursor = glm::vec2(start_x, game.grid->pos.y);
    cursor.y -= cam_offset.y;
    for (auto y = 0; y < game.grid->height; y++) {
        for (auto x = 0; x < game.grid->width; x++) {
            SDL_Rect rect = {
                int(cursor.x), int(cursor.y),
                int(cell_size), int(cell_size)
            };
            if (game.grid->has_entities(x, y)) {
                SDL_RenderFillRect(renderer, &rect);
            }
            else {
                SDL_RenderDrawRect(renderer, &rect);
            }
            cursor.x += cell_size;
        }
        cursor.x = start_x;
        cursor.y += cell_size;
    }

    // render all the entities here
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (auto& entity : game.entities) {
        this->draw_rect(entity->pos - cam_offset, entity->size);
    }

    // this->render_collision_flags(game);
    // glm::vec2 dims = glm::vec2(this->width, this->height);
    // glm::vec2 p = dims / 2.0f;
    // glm::vec2 m = game.get_mouse_pos();
    // this->draw_plane(p, m - p);

    draw_frame_rate(game.dt);
    draw_entity_count(game.entities.size());
    draw_scores(game);
    SDL_RenderPresent(renderer);
}

void Graphics::draw_rect(glm::vec2 pos, glm::vec2 size) {
    SDL_Rect rect = { int(pos.x), int(pos.y),int(size.x), int(size.y) };
    SDL_RenderFillRect(renderer, &rect);
}

void Graphics::draw_centered_rect(glm::vec2 pos, glm::vec2 size) {
    SDL_Rect rect = {
        int(pos.x) - int(size.x) / 2,
        int(pos.y) - int(size.y) / 2,
        int(size.x), int(size.y)
    };
    SDL_RenderFillRect(renderer, &rect);
}


void Graphics::draw_line(glm::vec2 p1, glm::vec2 p2) {
    SDL_RenderDrawLine(renderer, int(p1.x), int(p1.y), int(p2.x), int(p2.y));
}

void Graphics::draw_plane(glm::vec2 p, glm::vec2 dir) {
    glm::vec2 normal = glm::normalize(dir);

    //  draw plane epicenter
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    glm::vec2 s = glm::vec2(5, 5);
    this->draw_centered_rect(p, s);

    //  draw normal    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    this->draw_line(p, p + normal * 50.0f);

    // draw the ray
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    glm::vec2 right = glm::rotate(normal, 3.1415926535f / 2.0f);
    glm::vec2 left = -right;

    float length = 400;
    glm::vec2 right_most = p + right * length;
    glm::vec2 left_most = p + left * length;
    this->draw_line(p, right_most);
    this->draw_line(p, left_most);

    int num_divisions = 30;
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    glm::vec2 jump = (right_most - left_most) / float(num_divisions);
    glm::vec2 start = left_most;
    for (int i = 0; i <= num_divisions; i++) {
        this->draw_line(start, start - normal * 500.0f);
        start += jump;
    }

    // shade the area somehow

    // put a little triangle at the end
    // draw line going out infinitely. 
    // somehow shade the zone


}


void Graphics::render_collision_flags(Game& game) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (auto& entity : game.entities) {
        std::vector<Entity*> hits = game.grid->query(entity->pos, entity->get_br());
        bool intersected = false;
        for (auto& against_entity : hits) {
            if (entity->id == against_entity->id) {
                continue;
            }
            if (entity->intersects(against_entity)) {
                intersected = true;
                break;
            }
        }
        if (intersected) {
            SDL_Rect rect = {
                    int(entity->pos.x),
                    int(entity->pos.y),
                    5, 5
            };
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Graphics::draw_scores(Game& game) {
    int quarterw = game.graphics->width / 8;
    int quarterh = game.graphics->height / 8;

    // draw player score
    {
        const SDL_Color color = { 0, 255, 0, 255 };
        char fps_str[32];
        sprintf(fps_str, "%i", game.player_score);
        draw_text(fps_str, color, quarterw, quarterh);
    }

    // draw enemy score
    {
        const SDL_Color color = { 255, 0, 0, 255 };
        char fps_str[32];
        sprintf(fps_str, "%i", game.enemy_score);
        draw_text(fps_str, color,
            game.graphics->width - quarterw, quarterh);
    }
}


void Graphics::load_sprite_resources(
    Graphics* graphics
) {
    // // load in human sprite
    // int human_sprite_num_anims = 4;
    // int * human_sprite_anim_lengths = malloc(sizeof(int) * 4);
    // human_sprite_anim_lengths[0] = 4;
    // human_sprite_anim_lengths[1] = 4;
    // human_sprite_anim_lengths[2] = 4;
    // human_sprite_anim_lengths[3] = 4;
    // struct Sprite_resource *human_sprite_resource = sprite_resource_new(
    //     game.renderer, 
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
