#pragma once

#include <Common/ECS/World.hpp>
#include <Common/Component/Transform.hpp>
#include <Client/Components/Sprite.hpp>
#include <Client/RenderTarget/RenderTarget.hpp>

class RenderSystem : public ECS::System {
public:
    void init();
    void update(float delta, std::shared_ptr<ECS::World>& world, Rtype::RenderTarget& target);

    typedef std::tuple<const ECS::ComponentHandle<SpriteComponent>, const ECS::ComponentHandle<Rtype::TransformComponent>> Dependencies;

    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};