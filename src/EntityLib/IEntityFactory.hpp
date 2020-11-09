#pragma once

#include "ECS/World.hpp"

namespace Rtype
{
    class IEntityFactory{

    public:
        virtual ~IEntityFactory();
        virtual void instanciate(std::shared_ptr<ECS::World>&) = 0;
    };
} 