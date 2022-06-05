#pragma once

#include <stdexcept>
#include <vector>

#include <entt/entt.hpp>
#include <SDL2/SDL.h>

#include "Components.hpp"
#include "Graphics.hpp"


class System
{
public:
    System() = default;
    virtual ~System() = default;
    int getSortOrder() const { return sortOrder; }
    void setSortOrder(int sortOrder) { this->sortOrder = sortOrder; }
    void virtual process(double deltaTime) { throw std::runtime_error("Not implemented"); };

protected:
    int sortOrder = 0;
};


class Systems
{
public:
    Systems() = default;
    ~Systems() = default;
    void addSystem(System* system);
    void addSystem(System* system, int sortOrder);
    void removeSystem(System* system);
    void process(double deltaTime);

private:
    std::vector<System*> systems;
};


class RenderSystem : public System
{
public:
    RenderSystem(Graphics* graphics);
    ~RenderSystem();

    glm::vec2 getWindowSize();
    void process(double deltaTime);

private:
    Graphics* graphics;
    std::map<int, SDL_Texture*> textures;
};


class LifeSystem : public System
{
public:
    void process(double deltaTime);
};


class MovementSystem : public System
{
public:
    MovementSystem(glm::vec2 bounds);
    void process(double deltaTime);

private:
    glm::vec2 bounds;
};