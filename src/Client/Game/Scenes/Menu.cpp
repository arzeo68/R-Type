#include <iostream>
#include <Client/Game/Scenes/Menu.hpp>
#include <Client/Components/TextureLibrary.hpp>
#include <Client/Components/Sprite.hpp>
#include <Client/Components/Rotation.hpp>
#include <Common/Component/Transform.hpp>
#include <Common/Component/Movement.hpp>

#include <Client/Game/Systems/RenderSystem.hpp>
#include <Common/Systems/MovementUpdateSystem.hpp>
#include <Common/Systems/TransformSystem.hpp>

static void base_update_routine(float delta, ECS::ComponentHandle<Rtype::MovementComponent> comp)
{ }

void MenuScene::onCreate()
{
    std::cout << "Creating MenuScene\n";
    m_World = std::make_shared<ECS::World>();
    m_World->initialize();

    m_World->registerComponent<TextureLibraryComponent>();
    m_World->registerComponent<SpriteComponent>();
    m_World->registerComponent<TextureComponent>();
    m_World->registerComponent<Rtype::TransformComponent>();
    m_World->registerComponent<Rtype::MovementComponent>();

    m_World->addSingletonComponents<TextureLibraryComponent>(
        TextureLibraryComponent()
    );

    m_World->registerSystem<RenderSystem>();
    m_World->setSystemSignature<RenderSystem, SpriteComponent, Rtype::TransformComponent>();

    m_World->registerSystem<Rtype::MovementUpdateSystem>();
    m_World->setSystemSignature<Rtype::MovementUpdateSystem, Rtype::MovementComponent>();

    m_World->registerSystem<Rtype::TransformSystem>();
    m_World->setSystemSignature<Rtype::TransformSystem, Rtype::TransformComponent, Rtype::MovementComponent>();

    auto texlib = m_World->getSingletonComponent<TextureLibraryComponent>();

    texlib.get()->load_default_texture("../ressources/default.png");

    ECS::Entity e = m_World->createEntity();

    m_World->addComponents<SpriteComponent, Rtype::TransformComponent, Rtype::MovementComponent>(
        e,
        SpriteComponent(texlib.get()->get_texture("<default>"), 0),
        Rtype::TransformComponent({1920 / 2, 1080 / 2}, 0, {1, 1}),
        Rtype::MovementComponent({0, 0}, 0.1f, std::bind(base_update_routine, std::placeholders::_1, std::placeholders::_2))
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

void MenuScene::update(float delta, Rtype::RenderTarget& target)
{
    target.expose().clear(Rtype::color::Black);
    m_World->getSystem<Rtype::MovementUpdateSystem>()->update(delta, m_World);
    m_World->getSystem<Rtype::TransformSystem>()->update(delta, m_World);
    m_World->getSystem<RenderSystem>()->update(delta, m_World, target);
}

void MenuScene::lateUpdate(float delta, Rtype::RenderTarget& target)
{ }