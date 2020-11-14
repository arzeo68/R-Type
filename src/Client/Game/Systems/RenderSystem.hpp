#pragma once

#include <Common/ECS/World.hpp>
#include <Common/Component/Transform.hpp>
#include <Client/Components/Sprite.hpp>
#include <Client/RenderTarget/RenderTarget.hpp>

/**
 * this system is used to render the entity
 */
class RenderSystem : public ECS::System {
public:
    /**
     * this function init the system
     */
    void init();
    /**
 * this function is called at each frame
 */
    void update(float delta, std::shared_ptr<ECS::World>& world, Rtype::RenderTarget& target);

    typedef std::tuple<const ECS::ComponentHandle<SpriteComponent>, const ECS::ComponentHandle<Rtype::TransformComponent>> Dependencies;
    /**
 * this function return all the dependencies needed by the render system
 */
    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};