#include <algorithm>
#include <Client/Components/NetworkUpdate.hpp>
#include <Client/Game/Systems/NetworkEntityDestructionSystem.hpp>

void NetworkEntityDestructionSystem::init()
{ }

void NetworkEntityDestructionSystem::update(float delta, std::shared_ptr<ECS::World>& world)
{
   auto netupdate = world->getSingletonComponent<RType::NetworkUpdateSingletonComponent>();

   if (netupdate.get()->destructionIDs.empty())
      return;
   for (auto entity : m_cEntities) {
      auto [ id ] = getDependencies(entity, world);

      if (std::find(netupdate.get()->destructionIDs.begin(), netupdate.get()->destructionIDs.end(), id.get()->id) != netupdate.get()->destructionIDs.end()) {
         std::cout << "Destroying entity " << entity << "\n";
         world->deferEntityDestruction(entity);
      }
   }
   netupdate.get()->destructionIDs.clear();
}

NetworkEntityDestructionSystem::Dependencies NetworkEntityDestructionSystem::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const id = world->getComponent<RType::UniqueID>(entity);

    return std::make_tuple(id);
}