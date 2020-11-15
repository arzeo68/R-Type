#pragma once

#include <memory>
#include <functional>
#include "IEntityFactory.hpp"

class __declspec(dllexport) BasicShipFactory : public RType::IEntityFactory
{
private:
    /*Vector*/
    /*HP*/
    /*..*/

public:
    BasicShipFactory() = default;
    ~BasicShipFactory() = default;

    ECS::NetworkPacket instanciate(std::shared_ptr<ECS::World>& world, std::shared_ptr<UniqueIDGenerator>& idgenerator) override;

    std::string getName() const override
    {
        return std::string("BasicShip");
    }
};