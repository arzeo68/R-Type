#pragma once

#include <functional>
#include <Client/typeEncapsulation.hpp>
#include <Common/ECS/World.hpp>

namespace Rtype
{

    struct HitboxComponent {
        fRect box;
        std::function<void(ECS::ComponentHandle<HitboxComponent>&, std::shared_ptr<ECS::World>&, ECS::Entity, ECS::Entity)> handler;

        HitboxComponent() = default;

        template<typename func>
        HitboxComponent(fRect hitbox, func&& handler)
            : box(hitbox), handler(std::forward<func>(handler))
        { }
    };

} // namespace Rtype
