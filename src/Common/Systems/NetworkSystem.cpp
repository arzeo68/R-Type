#include <Common/Component/OutputQueue.hpp>
#include <Common/Component/Transform.hpp>
#include <Common/Systems/NetworkSystem.hpp>
#include <Common/ECS/NetworkPacket.hpp>

#include <iostream>
namespace RType
{

void NetworkSystem::init()
{ }

void NetworkSystem::update(float delta, std::shared_ptr<ECS::World>& world)
{
    auto oq = world->getSingletonComponent<RType::OutputQueueComponent>();
    for (ECS::Entity e : m_cEntities) {
        ECS::NetworkPacket p;
        auto [ id ] = getDependencies(e, world);
        auto const transform = world->getComponent<RType::TransformComponent>(e);

        p.id = id.get()->id;
        p.type = 1;
        p.x = transform.get()->position.x;
        p.y = transform.get()->position.y;
        oq.get()->OutputQueue.push_back(p);
    }
}

NetworkSystem::Dependencies NetworkSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const id = world->getComponent<RType::UniqueID>(entity);

    return std::tuple(id);
}

} // namespace RType