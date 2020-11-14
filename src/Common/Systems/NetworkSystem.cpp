#include <Common/Component/OutputQueue.hpp>
#include <Common/Component/Transform.hpp>
#include <Common/Systems/NetworkSystem.hpp>
#include <Common/ECS/NetworkPacket.hpp>

namespace Rtype
{

void NetworkSystem::init()
{ }

void NetworkSystem::update(float delta, std::shared_ptr<ECS::World>& world)
{
    Rtype::NetworkPacketType type = Rtype::NPT_UPDATE;
    auto oq = world->getSingletonComponent<Rtype::OutputQueueComponent>();
    for (ECS::Entity e : m_cEntities) {
        ECS::NetworkPacket p;
        auto [ id ] = getDependencies(e, world);
        auto const transform = world->getComponent<Rtype::TransformComponent>(e);

        p.addData<Rtype::UniqueID>(id.get());
        p.addData<Rtype::NetworkPacketType>(&type);
        p.addData<Rtype::TransformComponent>(transform.get());
        oq.get()->OutputQueue.push_back(p);
    }
}

NetworkSystem::Dependencies NetworkSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const id = world->getComponent<Rtype::UniqueID>(entity);

    return std::tuple(id);
}

} // namespace Rtype