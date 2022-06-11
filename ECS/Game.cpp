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
    // world.set<PlayMusic>({"music"});

    // FPS counter
    fpsText = world.entity()
            .add<WindowBound>()
            .set<Position>({{10, 5}})
            .set<Text>({"", {0, 200, 0, 255}, Align::TOP_LEFT});

    // Bouncing particle emitter
    world.entity()
            .add<WindowBound>()
            .set<ParticleEmitter>({0.01, 0, 0, -1, 0, 5, 30})
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
            .iter([this](flecs::iter it, Position *p)
                  {
                      grid->clear();
                      for (Uint8 i: it)
                      {

                          auto *v = it.entity(i).get<Volume>();
                          if (v != nullptr)
                          {
                              grid->add(it.entity(i), *p, *v);
                          }
                          else
                          {
                              grid->add(it.entity(i), *p, glm::vec2(1, 1));
                          }
                      }
                  })
            .add(flecs::PreUpdate);

    // System that plays music
    world.system<PlayMusic>()
            .iter([this](flecs::iter it, PlayMusic *m)
                  {
                      if (!m->isPlaying)
                      {
                          mixer->playMusic(m->music);
                          m->isPlaying = true;
                      }
                  });

    // System that will spawn particles
    world.system<Position, ParticleEmitter>()
            .iter([](flecs::iter it, Position *p, ParticleEmitter *pe)
                  {
                      for (Uint8 i: it)
                      {
                          if (pe[i].spawnTimer > 0)
                          {
                              pe[i].spawnTimer -= it.delta_time();
                              continue;
                          }
                          pe[i].spawnTimer = 0;
                          do
                          {
                              // create a new vector based on the emitter's angle
                              double angle = pe[i].angle;
                              if (angle == -1)
                              {
                                  angle = frand(0, 1) * 360;
                              }
                              else
                              {
                                  angle = pe[i].angle + frand(-1, 1) * pe[i].angleVariance;
                              }
                              // convert angle to radians
                              angle = (angle * (M_PI / 180));
                              // create a new velocity vector x and y
                              auto vy = (float) sin(angle);
                              auto vx = (float) cos(angle);
                              auto speed = frand(pe[i].speed, pe[i].speed * pe[i].speedVariance);
                              // Create a new particle
                              it.world().entity()
                                      .add<WindowBound>()
                                      .add<Particle>()
                                      .set<Position>({p[i]})
                                      .set<Velocity>({{vx * speed, vy * speed}})
                                      .set<Lifespan>({pe[i].lifespan, pe[i].lifespan});
                              pe[i].spawnTimer += frand(pe[i].spawnRate,
                                                        pe[i].spawnRate * pe[i].spawnRateVariance);
                          }
                          while (pe[i].spawnTimer < it.delta_time());
                      }
                  })
            .add(flecs::OnUpdate);

    // System that will move entities based on their velocity
    world.system<Position, Velocity>()
            .iter([](flecs::iter it, Position *p, Velocity *v)
                  {
                      for (Uint8 i: it)
                      {
                          p[i] += v[i] * it.delta_time();
                      }
                  })
            .add(flecs::OnUpdate);

    // System that will move keep entities within the window bounds
    world.system<Position, Velocity, WindowBound>()
            .iter([this](flecs::iter it, Position *p, Velocity *v, WindowBound *w)
                  {
                      for (Uint8 i: it)
                      {
                          bool bounced = false;
                          if (p[i].x < 0)
                          {
                              p[i].x = 0;
                              v[i].x *= -1;
                              bounced = true;
                          }
                          else if (p[i].x > (float) graphics->getScreenWidth())
                          {
                              p[i].x = (float) graphics->getScreenWidth();
                              v[i].x *= -1;
                              bounced = true;
                          }
                          if (p[i].y < 0)
                          {
                              p[i].y = 0;
                              v[i].y *= -1;
                              bounced = true;
                          }
                          else if (p[i].y > (float) graphics->getScreenHeight())
                          {
                              p[i].y = (float) graphics->getScreenHeight();
                              v[i].y *= -1;
                              bounced = true;
                          }
                          bool isEmitter = it.entity(i).has<ParticleEmitter>();
                          if (bounced && isEmitter) it.entity(i).set<PlaySound>({"sound"});
                      }
                  })
            .add(flecs::OnUpdate);



    // System that reduces the lifespan of entities
    world.system<Lifespan>()
            .iter([this](flecs::iter it, Lifespan *l)
                  {
                      for (Uint8 i: it)
                      {
                          l[i].time -= it.delta_time();
                          if (l[i].time <= 0)
                          {
                              it.entity(i).add<IsDead>();
                          }
                      }
                  })
            .add(flecs::OnUpdate);

    // System that will draw text to the screen
    world.system<Position, Text>()
            .iter([this](flecs::iter it, Position *p, Text *t)
                  {
                      for (Uint8 i: it)
                      {
                          graphics->drawText(t[i], p[i]);
                      }
                  })
            .add(flecs::OnUpdate);

    // System that will draw particles to the screen
    world.system<Position, Particle>()
            .iter([this](flecs::iter it, Position *p, Particle *pa)
                  {
                      for (Uint8 i: it)
                      {
                          graphics->drawRect(p[i], (Volume) {{1, 1}}, {255, 255, 255, 255});
                      }
                  })
            .add(flecs::OnUpdate);

    // System that plays sounds
    world.system<PlaySound>()
            .iter([this](flecs::iter it, PlaySound *s)
                  {
                      for (Uint8 i: it)
                      {
                          if (!s->isPlaying)
                          {
                              mixer->playSound(s->sound);
                              s->isPlaying = true;
                              it.entity(i).remove<PlaySound>();
                          }
                      }
                  });

    // System that will remove all dead entities
    world.system<IsDead>()
            .iter([](flecs::iter it)
                  {
                      for (Uint8 i: it)
                      {
                          it.entity(i).destruct();
                      }
                  })
            .add(flecs::PostUpdate);
}
