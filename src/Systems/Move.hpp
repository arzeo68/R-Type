#pragma once

#include <iostream>
#include <memory>
#include "ECS/System.hpp"

class MoveSystem : public ECS::System {
    public:
        void init();
        void update(std::shared_ptr<ECS::World>& world);

        typedef std::tuple<const ECS::ComponentHandle<VelocityComponent>, ECS::ComponentHandle<TransformComponent>> Dependencies;

        Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};