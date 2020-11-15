#pragma once

#include <functional>
#include "IEntityFactory.hpp"

Rtype::IEntityFactory *entry();

static void UpdateBasicShipMovement(float delta, std::shared_ptr<ECS::World>& world, ECS::Entity target)
{ }

class BascicShipFactory : public Rtype::IEntityFactory
{
private:
    /*Vector*/
    /*HP*/
    /*..*/

public:
    BascicShipFactory() = default;
    ~BascicShipFactory() = default;

    ECS::NetworkPacket instanciate(std::shared_ptr<ECS::World>& world, std::shared_ptr<UniqueIDGenerator>& idgenerator) override {
        ECS::Entity e = world->createEntity();
        int id = idgenerator->getID();

        world->template addComponents<Rtype::TransformComponent, Rtype::MovementComponent, Rtype::UniqueID, Rtype::TagComponent>(
            e,
            Rtype::TransformComponent({0, 0}, 0, {1, 1}),
            Rtype::MovementComponent({-0.2, 0}, 0, std::bind(Rtype::UpdateBasicShipMovement, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
            Rtype::UniqueID(id),
            Rtype::TagComponent("Ennemy")
        );

        return {id, 0, 0, 0, {10, 237, 14, 16}};
    }
};
