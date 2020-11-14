#pragma once

#include <iostream>
#include <functional>
#include <Common/Component/PlayerID.hpp>
#include <Common/Component/InputQueue.hpp>
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
    auto ID = world->getComponent<Rtype::PlayerID>(target);
    auto InputQueue = world->getSingletonComponent<Rtype::InputQueueComponent>();

    std::deque<int> inputs = InputQueue.get()->InputQueueMap[ID.get()->id];

    while (!inputs.empty()) {
        std::cout << "input.size() = " << inputs.size() << "\n";
        int key_val = inputs.front();

        //std::cout << "Processing key : " << key_val << " for client " << ID.get()->id << "\n";
        inputs.pop_front();
        std::cout << "input.size() = " << inputs.size() << "\n";
    }
}

} // namespace Rtype