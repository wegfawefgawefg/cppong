//
// Created by Kyle Dougan on 6/6/22.
//

#pragma once

#include "Utilities.h"


struct WindowBound
{
};


struct Particle
{
};


struct Dead
{
};


struct Volume
{
    float width;
    float height;
};

struct Position
{
    float x;
    float y;
};


struct Velocity
{
    float x;
    float y;
};


struct Acceleration
{
    float x;
    float y;
};


struct Text
{
    std::string text;
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
