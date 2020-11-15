#pragma once

#include <Common/ECS/World.hpp>
#include <Common/Component/UniqueID.hpp>
/**
 * this system is used to render the entity
 */
class NetworkEntityDestructionSystem : public ECS::System {
public:
    /**
     * this function init the system
     */
    void init();
    /**
 * this function is called at each frame
 */
    void update(float delta, std::shared_ptr<ECS::World>& world);

    typedef std::tuple<const ECS::ComponentHandle<RType::UniqueID>> Dependencies;
    /**
 * this function return all the dependencies needed by the render system
 */
    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};