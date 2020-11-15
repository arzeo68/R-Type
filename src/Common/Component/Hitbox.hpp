#pragma once

#include <functional>
#include <Common/Component/Tag.hpp>
#include <Common/Component/UniqueID.hpp>
#include <Server/Network/Worker/ThreadSafeQueue.hpp>
#include <Client/typeEncapsulation.hpp>
#include <Common/ECS/World.hpp>

namespace RType
{

    static void PlayerCollisionUpdateRoutine(std::shared_ptr<RType::Network::ThreadSafeQueue<ECS::NetworkPacket>>& queue, float delta, std::shared_ptr<ECS::World>& world, ECS::Entity self, ECS::Entity target)
    { }

    static void BulletCollisionUpdateRoutine(std::shared_ptr<RType::Network::ThreadSafeQueue<ECS::NetworkPacket>>& queue, float delta, std::shared_ptr<ECS::World>& world, ECS::Entity self, ECS::Entity target)
    {
        auto const tag = world->getComponent<RType::TagComponent>(target);

        if (tag.get()->tag == "Enemy") {
            auto ID = world->getComponent<RType::UniqueID>(self);
            queue->add({static_cast<int>(ID.get()->id), 2, 0, 0, {0, 0, 0, 0}});
            world->deferEntityDestruction(self);
        }
    }

    struct HitboxComponent {
        fRect box;
        std::function<void(float, std::shared_ptr<ECS::World>&, ECS::Entity, ECS::Entity)> handler;

        HitboxComponent() = default;

        template<typename func>
        HitboxComponent(fRect hitbox, func&& handler)
            : box(hitbox), handler(std::forward<func>(handler))
        { }
    };

} // namespace RType
