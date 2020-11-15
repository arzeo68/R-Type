#include <iostream>
#include <Client/Game/Scenes/Menu.hpp>
#include <Client/Components/TextureLibrary.hpp>
#include <Client/Components/NetworkUpdate.hpp>
#include <Client/Components/Sprite.hpp>
#include <Common/Component/Transform.hpp>
#include <Common/Component/Movement.hpp>
#include <Common/Component/Hitbox.hpp>
#include <Common/Component/UniqueID.hpp>

#include <Client/Game/Systems/RenderSystem.hpp>
#include <Client/Game/Systems/NetworkEntityDestructionSystem.hpp>
#include <Common/Systems/MovementUpdateSystem.hpp>
#include <Common/Systems/TransformSystem.hpp>
#include <Common/Systems/PhysicSystem.hpp>

void base_update_routine(float delta, std::shared_ptr<ECS::World>& world, ECS::Entity target)
{
    auto input = world->getSingletonComponent<RType::NetworkUpdateSingletonComponent>();
    auto transform = world->getComponent<RType::TransformComponent>(target);
    auto ID = world->getComponent<RType::UniqueID>(target);

    for (auto p : input.get()->packets) {
        if (p.id == ID.get()->id) {
            transform.get()->position.x = p.x;
            transform.get()->position.y = p.y;
        }
    }
}

static void parrallax_update_routine(float delta, std::shared_ptr<ECS::World>& world, ECS::Entity target)
{
    auto transform = world->getComponent<RType::TransformComponent>(target);
    auto movement = world->getComponent<RType::MovementComponent>(target);

    transform.get()->position += movement.get()->speed * delta;
    if (transform.get()->position.x < -4096 + (1920 / 2))
        transform.get()->position.x = 4096 + (1920 / 2);
}

void MenuScene::onCreate()
{
    std::cout << "Creating MenuScene\n";
    m_World = std::make_shared<ECS::World>();
    m_World->initialize();

    m_World->registerComponent<TextureLibraryComponent>();
    m_World->registerComponent<RType::NetworkUpdateSingletonComponent>();
    m_World->registerComponent<SpriteComponent>();
    m_World->registerComponent<TextureComponent>();
    m_World->registerComponent<RType::TransformComponent>();
    m_World->registerComponent<RType::MovementComponent>();
    m_World->registerComponent<RType::UniqueID>();

    m_World->addSingletonComponents<TextureLibraryComponent, RType::NetworkUpdateSingletonComponent>(
        TextureLibraryComponent(),
        RType::NetworkUpdateSingletonComponent()
    );

    m_World->registerSystem<RenderSystem>();
    m_World->setSystemSignature<RenderSystem, SpriteComponent, RType::TransformComponent>();

    m_World->registerSystem<RType::MovementUpdateSystem>();
    m_World->setSystemSignature<RType::MovementUpdateSystem, RType::MovementComponent>();

    m_World->registerSystem<NetworkEntityDestructionSystem>();
    m_World->setSystemSignature<NetworkEntityDestructionSystem, RType::UniqueID>();

    auto texlib = m_World->getSingletonComponent<TextureLibraryComponent>();

    texlib.get()->load_default_texture("../../ressources/default.png");
    texlib.get()->load_texture("P_Background", "../../ressources/Nebula Aqua-Pink.png");
    texlib.get()->load_texture("P_Star1", "../../ressources/Stars Small_1.png");
    texlib.get()->load_texture("P_Star2", "../../ressources/Stars Small_2.png");
    texlib.get()->load_texture("P_Star3", "../../ressources/Stars-Big_1_1_PC.png");
    texlib.get()->load_texture("P_Star4", "../../ressources/Stars-Big_1_2_PC.png");
    texlib.get()->load_texture("P_Star4", "../../ressources/Stars-Big_1_2_PC.png");
    texlib.get()->load_texture("SpriteSheet", "../../ressources/Sprite_rtype.png");

    ECS::Entity parallax_background = m_World->createEntity();

    m_World->addComponents<SpriteComponent, RType::TransformComponent, RType::MovementComponent>(
        parallax_background,
        SpriteComponent(texlib.get()->get_texture("P_Background"), 0),
        RType::TransformComponent({0, 0}, 0, {1, 1}),
        RType::MovementComponent({-0.01, 0}, 0, std::bind(parrallax_update_routine, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
    );

    ECS::Entity parallax_star1 = m_World->createEntity();

    m_World->addComponents<SpriteComponent, RType::TransformComponent, RType::MovementComponent>(
        parallax_star1,
        SpriteComponent(texlib.get()->get_texture("P_Star1"), 0),
        RType::TransformComponent({0, 0}, 0, {1, 1}),
        RType::MovementComponent({-0.05, 0}, 0, std::bind(parrallax_update_routine, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
    );

    ECS::Entity parallax_star2 = m_World->createEntity();

    m_World->addComponents<SpriteComponent, RType::TransformComponent, RType::MovementComponent>(
        parallax_star2,
        SpriteComponent(texlib.get()->get_texture("P_Star2"), 0),
        RType::TransformComponent({2048, 0}, 0, {1, 1}),
        RType::MovementComponent({-0.1, 0}, 0, std::bind(parrallax_update_routine, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
    );

    ECS::Entity parallax_star3 = m_World->createEntity();

    m_World->addComponents<SpriteComponent, RType::TransformComponent, RType::MovementComponent>(
        parallax_star3,
        SpriteComponent(texlib.get()->get_texture("P_Star3"), 0),
        RType::TransformComponent({0, 0}, 0, {1, 1}),
        RType::MovementComponent({-0.5, 0}, 0, std::bind(parrallax_update_routine, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
    );

    ECS::Entity parallax_star4 = m_World->createEntity();

    m_World->addComponents<SpriteComponent, RType::TransformComponent, RType::MovementComponent>(
        parallax_star4,
        SpriteComponent(texlib.get()->get_texture("P_Star4"), 0),
        RType::TransformComponent({2048, 0}, 0, {1, 1}),
        RType::MovementComponent({-0.5, 0}, 0, std::bind(parrallax_update_routine, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
    );
}

void MenuScene::onDestroy()
{
    std::cout << "Destroying MenuScene\n";
}

void MenuScene::onActivate()
{
    std::cout << "Activating MenuScene\n";
}

void MenuScene::onDeactivate()
{
    std::cout << "Deactivating MenuScene\n";
}

void MenuScene::update(float delta, RType::RenderTarget& target)
{
    auto net_update = m_World->getSingletonComponent<RType::NetworkUpdateSingletonComponent>();
    m_World->clearDeferList();
    target.expose().clear(RType::color::Black);
    m_World->getSystem<RType::MovementUpdateSystem>()->update(delta, m_World);
    m_World->getSystem<NetworkEntityDestructionSystem>()->update(delta, m_World);
    m_World->getSystem<RenderSystem>()->update(delta, m_World, target);
    net_update.get()->packets.clear();
}

void MenuScene::lateUpdate(float delta, RType::RenderTarget& target)
{ }
