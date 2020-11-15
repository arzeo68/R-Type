#pragma once

#include <vector>
#include <memory>
#include <Common/ECS/NetworkPacket.hpp>

namespace RType
{

struct OutputQueueComponent {
    std::shared_ptr<std::vector<ECS::NetworkPacket>> OutputQueue;

    OutputQueueComponent() : OutputQueue(std::make_shared<std::vector<ECS::NetworkPacket>>()) {};
};

} // namespace RType
