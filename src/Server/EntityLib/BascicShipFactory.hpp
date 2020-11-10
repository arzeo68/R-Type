#pragma once

#include"IEntityFactory.hpp"

class BascicShipFactory : public Rtype::IEntityFactory
{
private:
    /*Vector*/
    /*HP*/
    /*..*/

public:
    BascicShipFactory() = default;
    ~BascicShipFactory() = default;

    void instanciate(std::shared_ptr<ECS::World>&);
};
