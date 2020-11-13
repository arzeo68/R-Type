#pragma once

#include <Common/ECS/World.hpp>
#include <Common/Component/Transform.hpp>
#include <Common/Component/Hitbox.hpp>

namespace Rtype
{

class PhysicSystem : public ECS::System {
public:
    void init();
    void update(float delta, std::shared_ptr<ECS::World>& world);

    typedef std::tuple<ECS::ComponentHandle<TransformComponent>, ECS::ComponentHandle<HitboxComponent>> Dependencies;

    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};


} // namespace Rtype