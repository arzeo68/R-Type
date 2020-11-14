#include <Common/Systems/TransformSystem.hpp>

namespace Rtype
{

void TransformSystem::init()
{ }

void TransformSystem::update(float delta, std::shared_ptr<ECS::World>& world)
{
    for (auto entity : m_cEntities) {
        auto [ transform, movement ] = getDependencies(entity, world);

        transform.get()->position += movement.get()->speed * delta;
        transform.get()->angle += movement.get()->angle * delta;
        if (transform.get()->angle < 0)
            transform.get()->angle = 360.f;
        else if (transform.get()->angle > 360)
            transform.get()->angle = 0.f;
        std::cout << "Entity " << entity << " : " << transform.get()->position.x << ", " << transform.get()->position.y << "\n";
    }
}

TransformSystem::Dependencies TransformSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto transform = world->getComponent<TransformComponent>(entity);
    auto const movement = world->getComponent<MovementComponent>(entity);

    return std::tuple(transform, movement);
}

} // namespace Rtype
