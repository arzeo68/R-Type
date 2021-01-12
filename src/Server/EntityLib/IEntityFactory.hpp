#pragma once

#include <string>
#include <Server/Network/Worker/ThreadSafeQueue.hpp>
#include "Common/unique_id.hpp"
#include "Common/ECS/NetworkPacket.hpp"
#include "Common/ECS/World.hpp"

namespace RType
{
    class IEntityFactory {
    public:
        virtual ~IEntityFactory() {};
        virtual ECS::NetworkPacket instanciate(std::shared_ptr<ECS::World>&, std::shared_ptr<UniqueIDGenerator>&, std::shared_ptr<RType::Network::ThreadSafeQueue<ECS::NetworkPacket>>&) = 0;
        virtual std::string getName() const = 0;
    };

}