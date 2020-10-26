#include "Components/Transform.hpp"
#include "Components/Velocity.hpp"
#include "ECS/World.hpp"
#include "Move.hpp"

void MoveSystem::init()
{ }

void MoveSystem::update(std::shared_ptr<ECS::World>& world)
{
    for (auto const& entity : m_cEntities) {
        auto [ velocity, transform ] = getDependencies(entity, world);

        (*transform.get())->x += (*velocity.get())->x;
        (*transform.get())->y += (*velocity.get())->y;
    }
}

MoveSystem::Dependencies MoveSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const velocity = world->getComponent<VelocityComponent>(entity);
    auto position = world->getComponent<TransformComponent>(entity);

    return std::make_tuple(velocity, position);
}