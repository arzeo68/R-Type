#include <Common/Systems/MovementUpdateSystem.hpp>

namespace Rtype
{

void MovementUpdateSystem::init()
{ }

void MovementUpdateSystem::update(float delta, std::shared_ptr<ECS::World>& world)
{
    for (auto entity : m_cEntities) {
        auto [ movement ] = getDependencies(entity, world);

        movement.get()->update(delta, movement);
    }
}

MovementUpdateSystem::Dependencies MovementUpdateSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto movement = world->getComponent<MovementComponent>(entity);

    return std::tuple(movement);
}

} // namespace Rtype
