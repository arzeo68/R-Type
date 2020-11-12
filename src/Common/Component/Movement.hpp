#pragma once

#include <functional>
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
    std::function<void(float, ECS::ComponentHandle<MovementComponent>&)> update;
};

} // namespace Rtype