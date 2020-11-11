#pragma once

#include <Common/ECS/World.hpp>
#include <Common/Component/Transform.hpp>
#include <Client/Components/Rotation.hpp>

class RotationSystem : public ECS::System {
public:
    void init();
    void update(float delta, std::shared_ptr<ECS::World>& world);

    typedef std::tuple<const ECS::ComponentHandle<RotationComponent>, ECS::ComponentHandle<Rtype::TransformComponent>> Dependencies;

    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};