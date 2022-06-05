#include <iostream>

#include "Systems.hpp"
#include "Components.hpp"
#include "Utilities.hpp"
#include "Entity.hpp"

RenderSystem::RenderSystem(Graphics* graphics)
{
    this->graphics = graphics;
}


RenderSystem::~RenderSystem() {}


glm::vec2 RenderSystem::getWindowSize()
{
    return graphics->getWindowSize();
}


void RenderSystem::process(double deltaTime)
{
    entt::registry* registry = Entity::getInstance()->getRegistry();

    auto view1 = registry->view<Transform, Sprite>();
    for (auto entity : view1)
    {
        auto& transform = view1.get<Transform>(entity);
        auto& sprite = view1.get<Sprite>(entity);
        // get the texture from m_textures by its id
        SDL_Texture* texture = textures[sprite.textureId];
        SDL_Rect* dest = new SDL_Rect();
        dest->x = (int)transform.position.x;
        dest->y = (int)transform.position.y;
        dest->w = (int)(transform.size.x * transform.scale.x);
        dest->h = (int)(transform.size.y * transform.scale.y);
        graphics->render(texture, NULL, dest);
    }

    auto view2 = registry->view<Transform, Shape>();
    for (auto entity : view2)
    {
        auto& transform = view2.get<Transform>(entity);
        auto& shape = view2.get<Shape>(entity);
        switch (shape.shapeId)
        {
        case 0:
            SDL_Rect * rect = new SDL_Rect();
            rect->x = (int)transform.position.x;
            rect->y = (int)transform.position.y;
            rect->w = (int)(transform.size.x * transform.scale.x);
            rect->h = (int)(transform.size.y * transform.scale.y);
            graphics->renderRect(rect, shape.color);
            break;
        }
    }

    auto view3 = registry->view<Transform, Text>();
    for (auto entity : view3)
    {
        auto& transform = view3.get<Transform>(entity);
        auto& text = view3.get<Text>(entity);
        graphics->renderText(text.string, text.color, &transform.position);
    }
}