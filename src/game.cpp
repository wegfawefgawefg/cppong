#include <iostream>

#include "game.hpp"
#include "graphics.hpp"

Game::Game(){
    SDL_Init(SDL_INIT_EVERYTHING);
    graphics = new Graphics();
}

Game::~Game() {
    SDL_Quit();
}

void Game::run(){
    std::cout << "Game running" << std::endl;
    running = true;
    now = SDL_GetPerformanceCounter();
    
    while (running) {
        process_events();
        update();
        render();
    }
}

void Game::process_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        running = 0;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = 0;
                break;
        }
    }

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_Q]) {
        running = 0;
    } 
}

void Game::update() {
    Uint64 last = now;
    now = SDL_GetPerformanceCounter();
    dt = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
}

void Game::render() {
    graphics->render(*this); 
}
