#include "Systems.hpp"
#include "Random.hpp"
#include "Entity.hpp"

void LifeSystem::process(double deltaTime)
{
    entt::registry* registry = Entity::getInstance()->getRegistry();

    auto view = registry->view<Life>();

    for (auto [entity, life] : view.each())
    {
        life.age += (float)deltaTime;

        auto transform = registry->try_get<Transform>(entity);
        if (life.shrinksOverLifetime && transform)
            transform->scale = glm::vec2(life.age / life.lifespan);

        if (life.age >= life.lifespan)
        {
            auto spawner = registry->try_get<Spawner>(entity);
            if (transform && spawner)
                for (size_t i = 0; i < (int)frand(50, 100); i++)
                    Entity::getInstance()->createParticle(transform->position);
            registry->destroy(entity);
        }
    }
}