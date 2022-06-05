#include "Systems.hpp"
#include "Entity.hpp"

MovementSystem::MovementSystem(glm::vec2 bounds)
{
    this->bounds = bounds;
}

void MovementSystem::process(double deltaTime)
{
    entt::registry* registry = Entity::getInstance()->getRegistry();

    auto view2 = registry->view<Transform>();
    for (auto entity : view2)
    {
        auto& transform = view2.get<Transform>(entity);

        transform.position += transform.velocity * (float)deltaTime;
        transform.velocity.y += 98.0f * (float)deltaTime;

        if (transform.position.x < 0)
        {
            transform.position.x = 0;
            transform.velocity.x = -transform.velocity.x;
        }
        else if (transform.position.x > bounds.x)
        {
            transform.position.x = bounds.x;
            transform.velocity.x = -transform.velocity.x;
        }

        if (transform.position.y > bounds.y)
        {
            registry->destroy(entity);
            continue;
        }
    }
}