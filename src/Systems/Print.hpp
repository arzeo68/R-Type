#pragma once

#include <iostream>
#include <memory>
#include "ECS/World.hpp"

class PrintSystem : public ECS::System {
    public:
        void init();
        void update(std::shared_ptr<ECS::World>& world);

        typedef std::tuple<const ECS::ComponentHandle<TransformComponent>> Dependencies;

        Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};