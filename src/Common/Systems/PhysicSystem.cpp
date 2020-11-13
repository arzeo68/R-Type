#include <Common/Systems/PhysicSystem.hpp>

namespace Rtype
{

void PhysicSystem::init()
{ }

void PhysicSystem::update(float delta, std::shared_ptr<ECS::World>& world)
{
    for (ECS::Entity e1 : m_cEntities) {
        for (ECS::Entity e2 : m_cEntities) {
            if (e1 == e2)
                continue;
            auto [ e1_transform, e1_hitbox ] = getDependencies(e1, world);
            auto [ e2_transform, e2_hitbox ] = getDependencies(e2, world);

             sfmlTransform e1_t;
            sfmlTransform e2_t;
            e1_t.translate(e1_transform.get()->position).rotate(e1_transform.get()->angle).scale(e1_transform.get()->scale);
            e2_t.translate(e2_transform.get()->position).rotate(e2_transform.get()->angle).scale(e2_transform.get()->scale);

            if (e1_t.transformRect(e1_hitbox.get()->box).intersects(e2_t.transformRect(e2_hitbox.get()->box))) {
                e1_hitbox.get()->handler(e1_hitbox, world, e1, e2);
                e2_hitbox.get()->handler(e2_hitbox, world, e2, e1);
            }
        }
    }
}

PhysicSystem::Dependencies PhysicSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto transform = world->getComponent<TransformComponent>(entity);
    auto const hitbox = world->getComponent<HitboxComponent>(entity);

    return std::tuple(transform, hitbox);
}

} // namespace Rtype