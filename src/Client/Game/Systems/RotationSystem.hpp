#pragma once

#include <Common/ECS/World.hpp>
#include <Common/Component/Transform.hpp>
#include <Client/Components/Rotation.hpp>

/**
 * this system is used to rotate an entity
 */
class RotationSystem : public ECS::System {
public:
    /**
* this function is called at each frame
*/
    void init();
    /**
* this function is called at each frame
*/
    void update(float delta, std::shared_ptr<ECS::World>& world);

    typedef std::tuple<const ECS::ComponentHandle<RotationComponent>, ECS::ComponentHandle<Rtype::TransformComponent>> Dependencies;
    /**
 * this function return all the dependencies needed by the rotation system
 */
    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};