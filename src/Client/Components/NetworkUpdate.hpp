#pragma once

#include <vector>
#include "Common/ECS/NetworkPacket.hpp"

namespace Rtype
{

struct NetworkUpdateSingletonComponent {
    std::vector<ECS::NetworkPacket> packets;

    NetworkUpdateSingletonComponent() = default;
};

} // namespace Rtype
