//
// Created by Kyle Dougan on 6/6/22.
//
#include <iostream>

#include "Game.h"
#include "Components.h"
#include "Utilities.h"


Game::Game()
{
    graphics = new Graphics(screenWidth, screenHeight);
    mixer = new Mixer();
    grid = new Grid(glm::ivec2(screenWidth, screenHeight));

    setupSystems();
}


void Game::run()
{
    world.set<flecs::Rest>({});
    world.set_target_fps(120);
    world.set<PlayMusic>({"music"});

    // FPS counter
    fpsText = world.entity()
            .add<WindowBound>()
            .set<Position>({{10, 5}})
            .set<Text>({"", {0, 200, 0, 255}, Align::TOP_LEFT});

    // Bouncing particle emitter
    world.entity()
            .add<WindowBound>()
            .set<ParticleEmitter>({1.0 / 120, 0, 0, -1, 0, 5, 30})
            .set<Position>({{(float) screenWidth / 2, (float) screenHeight / 2}})
            .set<Velocity>({{frand(-2, 2) * 100, frand(-2, 2) * 100}});

    isRunning = true;
    while (isRunning)
    {
        handleEvents();
        graphics->clear();
        update();
        graphics->present();
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
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                }
                break;
        }
    }
}


void Game::update()
{
    float deltaTime = world.delta_time();
    Text *text = fpsText.get_mut<Text>();
    text->value = std::to_string(1 / deltaTime) + " fps";
    world.progress(0);
}


void Game::setupSystems()
{
    // update the world grid
    world.system<Position>()
            .iter([this](flecs::iter it, Position *position)
                  {
                      grid->clear();
                      for (Uint8 index: it)
                      {
                          auto *volume = it.entity(index).get<Volume>();
                          if (volume != nullptr)
                              grid->add(it.entity(index), *position, *volume);
                          else
                              grid->add(it.entity(index), *position, glm::vec2(1, 1));
                      }
                  })
            .add(flecs::PreUpdate);

    // System that plays music
    world.system<PlayMusic>()
            .each([this](flecs::iter &it, size_t index, PlayMusic &m)
                  {
                      if (!m.isPlaying)
                      {
                          mixer->playMusic(m.music);
                          m.isPlaying = true;
                      }
                  });

    // System that will spawn particles
    world.system<Position, ParticleEmitter>()
            .each([](flecs::iter &it, size_t index, Position &position, ParticleEmitter &emitter)
                  {
                      if (emitter.spawnTimer > 0)
                      {
                          emitter.spawnTimer -= it.delta_time();
                          return;
                      }
                      emitter.spawnTimer = 0;
                      do
                      {
                          // create a new vector based on the emitter's angle
                          double angle = emitter.angle;
                          if (angle == -1)
                          {
                              angle = frand(0, 1) * 360;
                          }
                          else
                          {
                              angle = emitter.angle + frand(-1, 1) * emitter.angleVariance;
                          }
                          // convert angle to radians
                          angle = (angle * (M_PI / 180));
                          // create a new velocity vector x and y
                          auto vy = (float) sin(angle);
                          auto vx = (float) cos(angle);
                          auto speed = frand(emitter.speed, emitter.speed * emitter.speedVariance);
                          // Create a new particle
                          it.world().entity()
                                  .add<WindowBound>()
                                  .add<Particle>()
                                  .set<Position>({position})
                                  .set<Velocity>({{vx * speed, vy * speed}})
                                  .set<Lifespan>({emitter.lifespan, emitter.lifespan});
                          emitter.spawnTimer += frand(emitter.spawnRate,
                                                      emitter.spawnRate * emitter.spawnRateVariance);
                      }
                      while (emitter.spawnTimer < it.delta_time());
                  })
            .add(flecs::OnUpdate);

    // System that will move entities based on their velocity
    world.system<Position, Velocity>()
            .each([this](flecs::iter &it, size_t index, Position &position, Velocity &velocity)
                  {
                      position += velocity * it.delta_time();
                  })
            .add(flecs::OnUpdate);

    world.system<Position, Velocity, const WindowBound>()
            .each([this](flecs::iter &it, size_t index, Position &position, Velocity &velocity,
                         const WindowBound &bound)
                  {
                      bool bounced = false;
                      if (position.x < 0)
                      {
                          position.x = 0;
                          velocity.x *= -1;
                          bounced = true;
                      }
                      else if (position.x > (float) graphics->getScreenWidth())
                      {
                          position.x = (float) graphics->getScreenWidth();
                          velocity.x *= -1;
                          bounced = true;
                      }
                      if (position.y < 0)
                      {
                          position.y = 0;
                          velocity.y *= -1;
                          bounced = true;
                      }
                      else if (position.y > (float) graphics->getScreenHeight())
                      {
                          position.y = (float) graphics->getScreenHeight();
                          velocity.y *= -1;
                          bounced = true;
                      }
                      bool isEmitter = it.entity(index).has<ParticleEmitter>();
                      if (bounced && isEmitter)
                      {
                          float pan = (position.x / (float) graphics->getScreenWidth()) * 2 - 1;
                          it.entity(index).set<PlaySound>({"sound", pan});
                      }

                  })
            .add(flecs::OnUpdate);

    // System that reduces the lifespan of entities
    world.system<Lifespan>()
            .each([](flecs::iter &it, size_t index, Lifespan &lifespan)
                  {
                      lifespan.time -= it.delta_time();
                      if (lifespan.time <= 0)
                      {
                          it.entity(index).add<IsDead>();
                      }
                  })
            .add(flecs::OnUpdate);

    // System that will draw text to the screen
    world.system<Position, Text>()
            .each([this](flecs::iter &it, size_t index, Position &position, Text &text)
                  {
                      graphics->drawText(text, position);
                  })
            .add(flecs::OnUpdate);

    // System that will draw particles to the screen
    world.system<Position, const Particle>()
            .each([this](flecs::iter &it, size_t index, Position &position, const Particle &particle)
                  {
                      graphics->drawRect(position, (Volume) {{1, 1}}, {255, 255, 255, 255});
                  })
            .add(flecs::OnUpdate);

    // System that plays sounds
    world.system<PlaySound>()
            .each([this](flecs::iter &it, size_t index, PlaySound &s)
                  {
                      if (!s.isPlaying)
                      {
                          mixer->playSound(s.sound, s.pan);
                          s.isPlaying = true;
                          it.entity(index).remove<PlaySound>();
                      }
                  });

    // System that will remove all dead entities
    world.system<const IsDead>()
            .each([](flecs::iter it, size_t index, const IsDead &dead)
                  {
                      it.entity(index).destruct();
                  })
            .add(flecs::PostUpdate);
}
