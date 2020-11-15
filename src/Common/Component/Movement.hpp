#pragma once

#include <iostream>
#include <functional>
#include <Server/Network/Worker/ThreadSafeQueue.hpp>
#include <Common/Component/UniqueID.hpp>
#include <Common/Component/PlayerID.hpp>
#include <Common/Component/Tag.hpp>
#include <Common/Component/InputQueue.hpp>
#include <Common/Component/Hitbox.hpp>
#include <Common/Component/Movement.hpp>
#include <Common/Component/Transform.hpp>
#include <Client/typeEncapsulation.hpp>
#include "Common/unique_id.hpp"

namespace RType
{

struct MovementComponent {
    MovementComponent() = default;

    template<typename func>
    MovementComponent(RType::vec2f base_speed, float base_angle, func&& update_routine)
        : speed(base_speed), angle(base_angle), update(std::forward<func>(update_routine))
    { }

    RType::vec2f speed;
    float angle;
    std::function<void(float, std::shared_ptr<ECS::World>&, ECS::Entity target)> update;
};

static void BulletUpdateMovement(std::shared_ptr<RType::Network::ThreadSafeQueue<ECS::NetworkPacket>>& queue, float delta, std::shared_ptr<ECS::World>& world, ECS::Entity target)
{
    auto const transform = world->getComponent<RType::TransformComponent>(target);

    if (transform.get()->position.x > 1000) {
        auto ID = world->getComponent<RType::UniqueID>(target);
        queue->add({static_cast<int>(ID.get()->id), 2, 0, 0, {0, 0, 0, 0}});
        world->deferEntityDestruction(target);
    }
}

static void PlayerUpdateMovement(std::shared_ptr<UniqueIDGenerator>& unique_id_generator, std::shared_ptr<RType::Network::ThreadSafeQueue<ECS::NetworkPacket>>& queue, float delta, std::shared_ptr<ECS::World>& world, ECS::Entity target)
{
    auto movement = world->getComponent<RType::MovementComponent>(target);
    auto ID = world->getComponent<RType::PlayerID>(target);
    auto InputQueue = world->getSingletonComponent<RType::InputQueueComponent>();
    auto const transform = world->getComponent<RType::TransformComponent>(target);

    std::deque<int>& inputs = InputQueue.get()->InputQueueMap[ID.get()->id];

    movement.get()->speed.x = 0;
    movement.get()->speed.y = 0;
    while (!inputs.empty()) {
        int key_val = inputs.front();

        switch (key_val) {
            case 73:
                movement.get()->speed.y = -0.4;
                break;
            case 72:
                movement.get()->speed.x = 0.5;
                break;
            case 74:
                movement.get()->speed.y = 0.4;
                break;
            case 71:
                movement.get()->speed.x = -0.5;
                break;
            case 57: {
                ECS::Entity e = world->createEntity();
                uint32_t id = unique_id_generator->getID();
                world->template addComponents<RType::TransformComponent, RType::MovementComponent, RType::HitboxComponent, RType::UniqueID, RType::TagComponent>(
                    e,
                    RType::TransformComponent({transform.get()->position.x + 20, transform.get()->position.y}, 0, {1, 1}),
                    RType::MovementComponent({0.9, 0}, 0, std::bind(RType::BulletUpdateMovement, queue, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
                    RType::HitboxComponent({0, 0, 22, 10}, std::bind(RType::BulletCollisionUpdateRoutine, queue, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)),
                    RType::UniqueID(id),
                    RType::TagComponent("Bullet")
                );
                queue->add({static_cast<int>(id), 0, transform.get()->position.x + 20, transform.get()->position.y, {7, 311, 22, 10}});
            }
            default:
                break;
        }
        inputs.pop_front();
    }
}

} // namespace RType