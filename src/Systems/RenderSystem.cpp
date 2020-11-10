#include "RenderSystem.hpp"
#include <iostream>

void RenderSystem::init()
{ }

void RenderSystem::update(float delta, std::shared_ptr<ECS::World>& world, sf::RenderWindow& window)
{
    sf::RenderStates states;
    for (auto const& entity : m_cEntities) {
        auto [ sprite, transform ] = getDependencies(entity, world);
        auto tmp = world->getSingletonComponent<TextureLibrarySingletonComponent>();

        sf::Transform mat = sf::Transform::Identity;
        mat.translate(transform.get()->pos);
        mat.scale(transform.get()->scale);
        mat.rotate(transform.get()->angle);
        states.transform = mat;

        window.draw(sprite.get()->sprite, states);
    }
}

RenderSystem::Dependencies RenderSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const sprite = world->getComponent<SpriteComponent>(entity);
    auto const transform = world->getComponent<TransformComponent>(entity);

    return std::make_tuple(sprite, transform);
}