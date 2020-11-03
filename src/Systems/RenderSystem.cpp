#include "RenderSystem.hpp"
#include <iostream>

void RenderSystem::init()
{ }

void RenderSystem::update(float delta, std::shared_ptr<ECS::World>& world, sf::RenderWindow& window, sf::Transform camera)
{
    sf::RenderStates states;
    for (auto const& entity : m_cEntities) {
        auto [ transform, rectangle ] = getDependencies(entity, world);

        sf::Transform mat = sf::Transform::Identity;
        mat.translate((*transform.get())->pos);
        mat.scale((*transform.get())->scale);
        mat.rotate((*transform.get())->angle);
        states.transform = mat;

        window.draw((*rectangle.get())->shape, states);
    }
}

RenderSystem::Dependencies RenderSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const transform = world->getComponent<TransformComponent>(entity);
    auto rectangle = world->getComponent<RectangleComponent>(entity);

    return std::make_tuple(transform, rectangle);
}