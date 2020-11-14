#pragma once

#include <vector>
#include <Common/ECS/NetworkPacket.hpp>

namespace Rtype
{

struct OutputQueueComponent {
    std::vector<ECS::NetworkPacket> OutputQueue;

    OutputQueueComponent() : OutputQueue({}) {};
};

} // namespace Rtype
