#pragma once

#include <vector>
#include <Common/ECS/NetworkPacket.hpp>

namespace RType
{

struct OutputQueueComponent {
    std::vector<ECS::NetworkPacket> OutputQueue;

    OutputQueueComponent() : OutputQueue({}) {};
};

} // namespace RType
