#include <iostream>
#include <unistd.h>
#include <type_traits>
#include <utility>
#include <typeindex>
#include "ECS/World.hpp"
#include "ECS/SingletonComponentCollection.hpp"

#include "Components/Transform.hpp"
#include "Components/Velocity.hpp"
#include "Components/Invisibility.hpp"
#include "Components/Tag.hpp"

#include "Systems/Move.hpp"
#include "Systems/Print.hpp"

int main()
{
    std::shared_ptr<ECS::World> world = std::make_shared<ECS::World>();

    world->initialize();

    world->registerComponent<TransformComponent>();
    world->registerComponent<VelocityComponent>();
    world->registerComponent<InvisibilityComponent>();
    world->registerComponent<TagComponent>();

    auto move_system = world->registerSystem<MoveSystem, InvisibilityComponent>();
    {
        world->setSystemSignature<MoveSystem, TransformComponent, VelocityComponent>();
    }
    move_system->init();

    auto print_system = world->registerSystem<PrintSystem>();
    {
        ECS::Signature signature;
        signature.set(world->getComponentType<TransformComponent>());
        world->setSystemSignature<PrintSystem>(signature);
    }

    std::vector<ECS::Entity> entities(20);
    for (auto& entity : entities) {
        entity = world->createEntity();

        world->addComponents<TransformComponent, VelocityComponent>(
            entity,
            TransformComponent{3.5, 3.5},
            VelocityComponent{1, 1}
        );
    }

    world->addComponent<InvisibilityComponent>(entities[10], InvisibilityComponent{'a'});

    int frame_count = 0;
    while (1) {
        move_system->update(world);
        print_system->update(world);

        if (frame_count == 3)
            world->removeComponent<InvisibilityComponent>(entities[10]);
        sleep(1);
        frame_count += 1;
    }

    return 0;
}