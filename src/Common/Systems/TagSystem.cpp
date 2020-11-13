/*
** EPITECH PROJECT, 2020
** RType
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "TagSystem.hpp"

void TagSystem::init()
{ }

void TagSystem::update(float delta, std::shared_ptr<ECS::World>& world)
{
    sf::RenderStates states;
    for (auto const& entity : m_cEntities) {
        auto [tag] = getDependencies(entity, world);
        std::cout << "tag compo: " << (*tag.get())->tag << std::endl;
    }
}

TagSystem::Dependencies TagSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const tag = world->getComponent<TagComponent>(entity);
    return std::make_tuple(tag);
}
