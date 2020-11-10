#pragma once

#include <set>
#include "Types.h"

namespace ECS
{

class System
{
    public:
        std::set<Entity> m_cEntities;
        std::vector<ComponentType> m_cIgnoredComponents;
};

} // namespace ECS
