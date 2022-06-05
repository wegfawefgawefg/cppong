#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "Components.hpp"

// Entity should be a singleton
class Entity
{
public:
    static Entity* getInstance();
    entt::registry* getRegistry() { return _registry; }

    static entt::entity createParticle(glm::vec2 position);
    static entt::entity createParticle(glm::vec2 position, bool isSpawner);

protected:
    entt::registry* _registry;

private:
    static Entity* _instance;
    Entity() : _registry(new entt::registry()) {}
    Entity(const Entity&);
    Entity& operator=(const Entity&);
};