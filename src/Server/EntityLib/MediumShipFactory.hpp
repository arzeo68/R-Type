#pragma once

#include <memory>
#include <functional>
#include "IEntityFactory.hpp"

class MediumShipFactory : public RType::IEntityFactory
{
private:
    /*Vector*/
    /*HP*/
    /*..*/

public:
    MediumShipFactory() = default;
    ~MediumShipFactory() = default;

    ECS::NetworkPacket instanciate(std::shared_ptr<ECS::World>& world, std::shared_ptr<UniqueIDGenerator>& idgenerator, std::shared_ptr<RType::Network::ThreadSafeQueue<ECS::NetworkPacket>>& queue) override;

    std::string getName() const override
    {
        return std::string("MediumShip");
    }
};