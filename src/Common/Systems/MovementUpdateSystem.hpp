#pragma once

#include <Common/ECS/World.hpp>
#include <Common/Component/Movement.hpp>
#include <Common/Component/Transform.hpp>

namespace RType
{

class MovementUpdateSystem : public ECS::System {
public:
    void init();
    void update(float delta, std::shared_ptr<ECS::World>& world);

    typedef std::tuple<ECS::ComponentHandle<MovementComponent>> Dependencies;

    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};


} // namespace RType