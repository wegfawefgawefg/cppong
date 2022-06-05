#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Graphics
{
public:
    Graphics();
    ~Graphics();

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    // getWindowSize shold return a 2d vector
    // with the width and height of the window
    glm::vec2 getWindowSize();

    SDL_Renderer* getRenderer() const { return renderer; }

    void drawText(const char* text, const SDL_Color color, const int x, const int y);
    void setWindowTitle(const char* text);
    void clear();
    void render(SDL_Texture* texture);
    void render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect);
    void renderRect(SDL_Rect* rect, const SDL_Color color);
    void renderText(std::string text, SDL_Color color, glm::vec2* position);
    void present();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
};