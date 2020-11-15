#pragma once

#include <vector>
#include "Common/ECS/NetworkPacket.hpp"

namespace Rtype
{

struct NetworkUpdateSingletonComponent {
    std::vector<ECS::NetworkPacket> packets;
    std::vector<int> destructionIDs;

    NetworkUpdateSingletonComponent() = default;
};

} // namespace Rtype
