#pragma once

#include <Common/ECS/World.hpp>
#include <Common/Component/UniqueID.hpp>

namespace Rtype {

class NetworkSystem : public ECS::System {
public:
    void init();
    void update(float delta, std::shared_ptr<ECS::World>& world);

    typedef std::tuple<const ECS::ComponentHandle<Rtype::UniqueID>> Dependencies;

    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};

}