#include "BasicShipFactory.hpp"

#include <Common/Component/Transform.hpp>
#include <Common/Component/Movement.hpp>
#include <Common/Component/Hitbox.hpp>
#include <Common/Component/UniqueID.hpp>

static void UpdateBasicShipMovement(float delta, std::shared_ptr<ECS::World>& world, ECS::Entity target)
{ }

ECS::NetworkPacket BasicShipFactory::instanciate(std::shared_ptr<ECS::World>& world, std::shared_ptr<UniqueIDGenerator>& idgenerator)
{
    ECS::Entity e = world->createEntity();
    int id = idgenerator->getID();
    world->template addComponents<RType::TransformComponent, RType::MovementComponent, RType::UniqueID, RType::TagComponent>(
        e,
        RType::TransformComponent({0, 0}, 0, {1, 1}),
        RType::MovementComponent({-0.2, 0}, 0, std::bind(UpdateBasicShipMovement, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
        RType::UniqueID(id),
        RType::TagComponent("Ennemy")
    );
    return {id, 0, 0, 0, {10, 237, 14, 16}};
}

__declspec(dllexport) RType::IEntityFactory *entry()
{
    return new BasicShipFactory();
}