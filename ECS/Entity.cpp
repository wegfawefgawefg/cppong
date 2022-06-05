#include "Entity.hpp"
#include "Utilities.hpp"

Entity* Entity::_instance = NULL;


Entity* Entity::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new Entity();
    }
    return _instance;
}

entt::entity Entity::createParticle(glm::vec2 position)
{
    return createParticle(position, false);
}


entt::entity Entity::createParticle(glm::vec2 position, bool isSpawner)
{
    entt::registry* registry = getInstance()->getRegistry();
    entt::entity entity = registry->create();
    registry->emplace<Transform>(
        entity,
        position,
        0.0f,
        glm::vec2(10, 10),
        glm::vec2(1, 1),
        glm::vec2(frand(-100, 100), frand(-100, 100))
        );
    registry->emplace<Life>(entity, 0.0f, frand(0.5f, 2.0f), true);
    SDL_Color color = { 255, 255, 255, 255 };
    registry->emplace<Shape>(entity, 0, color);
    if (isSpawner) registry->emplace<Spawner>(entity, 2);
    return entity;
}
