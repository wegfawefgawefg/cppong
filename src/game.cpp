#include <iostream>

#include "game.hpp"
#include "graphics.hpp"
#include "entity.hpp"

Game::Game(){
    graphics = new Graphics();
    // create 10 entities at random positions
    for(int i = 0; i < 10; i++){
        entities.push_back(new Entity(
            float(i) * 100.0,
            float(i) * 100.0,
            100.0, 100.0
        ));
    }
}

Game::~Game() {
    delete graphics;
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
