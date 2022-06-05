#pragma once

#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

struct Test
{
    int test;
};


struct Life
{
    float age;
    float lifespan;
    bool shrinksOverLifetime;
};


struct Spawner
{
    int generation;
};


struct Died {};


struct Transform
{
    glm::vec2 position;
    float rotation;
    glm::vec2 size;
    glm::vec2 scale;
    glm::vec2 velocity;
};


struct Sprite
{
    bool textureId;
};


struct Shape
{
    int shapeId;
    SDL_Color color;
};


struct Text
{
    std::string string;
    SDL_Color color;
};