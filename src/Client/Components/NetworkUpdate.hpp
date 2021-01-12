#pragma once

#include <vector>
#include "Common/ECS/NetworkPacket.hpp"

namespace RType
{

struct NetworkUpdateSingletonComponent {
    std::vector<ECS::NetworkPacket> packets;
    std::vector<int> destructionIDs;

    NetworkUpdateSingletonComponent() = default;
};

} // namespace RType
