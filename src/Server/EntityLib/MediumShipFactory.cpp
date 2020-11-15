#include <random>
#include "MediumShipFactory.hpp"

#include <Common/Component/Transform.hpp>
#include <Common/Component/Movement.hpp>
#include <Common/Component/Hitbox.hpp>
#include <Common/Component/UniqueID.hpp>

static void UpdateBasicShipMovement(std::shared_ptr<RType::Network::ThreadSafeQueue<ECS::NetworkPacket>>& queue, float delta, std::shared_ptr<ECS::World>& world, ECS::Entity target)
{
    auto const transform = world->getComponent<RType::TransformComponent>(target);

    if (transform.get()->position.x < -1000) {
        auto ID = world->getComponent<RType::UniqueID>(target);
        queue->add({static_cast<int>(ID.get()->id), 2, 0, 0, {0, 0, 0, 0}});
        world->deferEntityDestruction(target);
    }
}

static void UpdateBasicShipPhysic(std::shared_ptr<RType::Network::ThreadSafeQueue<ECS::NetworkPacket>>& queue, float delta, std::shared_ptr<ECS::World>& world, ECS::Entity self, ECS::Entity target)
{
    auto const tag = world->getComponent<RType::TagComponent>(target);

    if (tag.get()->tag == "Bullet") {
        auto ID = world->getComponent<RType::UniqueID>(self);
        queue->add({static_cast<int>(ID.get()->id), 2, 0, 0, {0, 0, 0, 0}});
        world->deferEntityDestruction(self);
    }
}


ECS::NetworkPacket MediumShipFactory::instanciate(std::shared_ptr<ECS::World>& world, std::shared_ptr<UniqueIDGenerator>& idgenerator, std::shared_ptr<RType::Network::ThreadSafeQueue<ECS::NetworkPacket>>& queue)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution{-540, 540};

    ECS::Entity e = world->createEntity();
    int id = idgenerator->getID();
    world->template addComponents<RType::TransformComponent, RType::MovementComponent, RType::HitboxComponent, RType::UniqueID, RType::TagComponent>(
        e,
        RType::TransformComponent({1000.f, static_cast<float>(distribution(gen))}, 0, {3, 3}),
        RType::MovementComponent({-0.2, 0}, 0, std::bind(UpdateBasicShipMovement, queue, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
        RType::HitboxComponent({0, 0, 27, 12}, std::bind(UpdateBasicShipPhysic, queue, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)),
        RType::UniqueID(id),
        RType::TagComponent("Enemy")
    );
    return {id, 0, 0, 0, {261, 208, 18, 18}};
}

EXPORT RType::IEntityFactory *entry()
{
    return new MediumShipFactory();
}