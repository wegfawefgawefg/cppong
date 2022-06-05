#include <string>
#include <iostream>
#include <string>

#include "Game.hpp"
#include "Graphics.hpp"
#include "Systems.hpp"
#include "Components.hpp"
#include "Entity.hpp"
#include "Utilities.hpp"

Game::Game()
{
    graphics = new Graphics();
    graphics->init("SDL EnTT Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
    running = false;
    deltaTime = 0;
    fps = 0;

    systems = new Systems();
    systems->addSystem(new LifeSystem(), 1);
    systems->addSystem(new MovementSystem(graphics->getWindowSize()), 2);
    systems->addSystem(new RenderSystem(graphics), 3);
}


Game::~Game()
{
    delete graphics;
}


void Game::run()
{
    running = true;
    while (running)
    {
        graphics->clear();
        handleEvents();
        update();
        render();
    }
}


void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                for (size_t i = 0; i < (int)frand(0, 100); i++)
                {
                    Entity::getInstance()->createParticle(
                        glm::vec2(event.button.x, event.button.y),
                        true
                    );
                }
                break;
            }
            break;
        }
    }
}


void Game::update()
{
    Uint32 now = SDL_GetTicks();
    deltaTime = (now - lastTime) * 0.001;
    lastTime = now;

    systems->process(deltaTime);
    fps = (float)(1.0 / deltaTime);
}


void Game::render()
{
    std::string fpsString = std::to_string(fps) + "fps";
    graphics->drawText(fpsString.c_str(), { 255,255,0,255 }, 10, 10);
    std::string entityCount = std::to_string(Entity::getInstance()->getRegistry()->alive());
    graphics->drawText(entityCount.c_str(), { 255,255,0,255 }, 10, 30);
    graphics->present();
}