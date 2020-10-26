#include "Components/Transform.hpp"
#include "Components/Tag.hpp"
#include "Print.hpp"

void PrintSystem::init()
{ }

void PrintSystem::update(std::shared_ptr<ECS::World>& world)
{
    for (auto const& entity : m_cEntities) {
        auto [ position ] = getDependencies(entity, world);

        std::cout << "Position of entity { " << entity << " } ( " << (*position.get())->x << ", " << (*position.get())->y << " )\n";
    }
}

PrintSystem::Dependencies PrintSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const position = world->getComponent<TransformComponent>(entity);

    return std::make_tuple(position);
}