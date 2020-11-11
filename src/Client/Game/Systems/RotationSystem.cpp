#include <Client/Game/Systems/RotationSystem.hpp>

void RotationSystem::init()
{ }

void RotationSystem::update(float delta, std::shared_ptr<ECS::World>& world)
{
    for (auto entity : m_cEntities) {
        auto [ rotation, transform ] = getDependencies(entity, world);

        transform.get()->angle = (transform.get()->angle + rotation.get()->rate >= 360) ? 0.f : (transform.get()->angle + rotation.get()->rate);
    }
}

RotationSystem::Dependencies RotationSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const rot = world->getComponent<RotationComponent>(entity);
    auto transform = world->getComponent<Rtype::TransformComponent>(entity);

    return std::make_tuple(rot, transform);
}