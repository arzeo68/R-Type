#pragma once

#include <iostream>
#include <functional>
#include <Common/Component/PlayerID.hpp>
#include <Common/Component/InputQueue.hpp>
#include <Common/Component/Movement.hpp>
#include <Client/typeEncapsulation.hpp>

namespace Rtype
{

struct MovementComponent {
    MovementComponent() = default;

    template<typename func>
    MovementComponent(Rtype::vec2f base_speed, float base_angle, func&& update_routine)
        : speed(base_speed), angle(base_angle), update(std::forward<func>(update_routine))
    { }

    Rtype::vec2f speed;
    float angle;
    std::function<void(float, std::shared_ptr<ECS::World>&, ECS::Entity target)> update;
};

static void PlayerUpdateMovement(float delta, std::shared_ptr<ECS::World>& world, ECS::Entity target)
{
    auto movement = world->getComponent<Rtype::MovementComponent>(target);
    auto ID = world->getComponent<Rtype::PlayerID>(target);
    auto InputQueue = world->getSingletonComponent<Rtype::InputQueueComponent>();

    std::deque<int>& inputs = InputQueue.get()->InputQueueMap[ID.get()->id];

    movement.get()->speed.x = 0;
    movement.get()->speed.y = 0;
    while (!inputs.empty()) {
        int key_val = inputs.front();

        switch (key_val) {
            case 73:
                std::cout << "Z" << std::endl;
                movement.get()->speed.x = 0.1;
                break;
            case 72:
                std::cout << "D" << std::endl;
                movement.get()->speed.y = 0.1;
                break;
            case 74:
                std::cout << "S" << std::endl;
                movement.get()->speed.x = -0.1;
                break;
            case 71:
                std::cout << "Q" << std::endl;
                movement.get()->speed.y = -0.1;
                break;
            case 57:
                std::cout << "Space" << std::endl;
                break;
            default:
                break;
        }
        inputs.pop_front();
    }
}

} // namespace Rtype