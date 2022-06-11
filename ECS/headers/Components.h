//
// Created by Kyle Dougan on 6/6/22.
//

#pragma once

#include <glm/glm.hpp>
#include "Utilities.h"

using namespace glm;

struct WindowBound
{
};


struct Particle
{
};


struct IsDead
{
};


struct Volume : vec2
{
};

struct Position : vec2
{
};


struct Velocity : vec2
{
};


struct Acceleration : vec2
{
};


struct Text
{
    std::string value;
    SDL_Color color;
    Align align;
};


struct Lifespan
{
    float time;
    float maxTime;
};


struct ParticleEmitter
{
    float spawnRate;
    float spawnRateVariance;
    float spawnTimer;
    float angle;
    float angleVariance;
    float lifespan;
    float speed;
    float speedVariance;
};


struct PlaySound
{
    std::string sound;
    bool loop;
    bool isPlaying;
};


struct PlayMusic
{
    std::string music;
    bool loop;
    bool isPlaying;
};
