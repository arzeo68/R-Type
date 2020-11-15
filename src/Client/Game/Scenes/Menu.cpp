#include <iostream>
#include <Client/Game/Scenes/Menu.hpp>
#include <Client/Components/TextureLibrary.hpp>
#include <Client/Components/NetworkUpdate.hpp>
#include <Client/Components/Sprite.hpp>
#include <Client/Components/Rotation.hpp>
#include <Common/Component/Transform.hpp>
#include <Common/Component/Movement.hpp>
#include <Common/Component/Hitbox.hpp>
#include <Common/Component/UniqueID.hpp>

#include <Client/Game/Systems/RenderSystem.hpp>
#include <Common/Systems/MovementUpdateSystem.hpp>
#include <Common/Systems/TransformSystem.hpp>
#include <Common/Systems/PhysicSystem.hpp>

void base_update_routine(float delta, std::shared_ptr<ECS::World>& world, ECS::Entity target)
{
    auto input = world->getSingletonComponent<Rtype::NetworkUpdateSingletonComponent>();
    auto transform = world->getComponent<Rtype::TransformComponent>(target);
    auto ID = world->getComponent<Rtype::UniqueID>(target);

    for (auto p : input.get()->packets) {
        if (p.id == ID.get()->id) {
            transform.get()->position.x = p.x;
            transform.get()->position.y = p.y;
        }
    }
}

void MenuScene::onCreate()
{
    std::cout << "Creating MenuScene\n";
    m_World = std::make_shared<ECS::World>();
    m_World->initialize();

    m_World->registerComponent<TextureLibraryComponent>();
    m_World->registerComponent<Rtype::NetworkUpdateSingletonComponent>();
    m_World->registerComponent<SpriteComponent>();
    m_World->registerComponent<TextureComponent>();
    m_World->registerComponent<Rtype::TransformComponent>();
    m_World->registerComponent<Rtype::MovementComponent>();
    m_World->registerComponent<Rtype::UniqueID>();

    m_World->addSingletonComponents<TextureLibraryComponent, Rtype::NetworkUpdateSingletonComponent>(
        TextureLibraryComponent(),
        Rtype::NetworkUpdateSingletonComponent()
    );

    m_World->registerSystem<RenderSystem>();
    m_World->setSystemSignature<RenderSystem, SpriteComponent, Rtype::TransformComponent>();

    m_World->registerSystem<Rtype::MovementUpdateSystem>();
    m_World->setSystemSignature<Rtype::MovementUpdateSystem, Rtype::MovementComponent, Rtype::UniqueID>();

    auto texlib = m_World->getSingletonComponent<TextureLibraryComponent>();

    texlib.get()->load_default_texture("../../ressources/default.png");
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
    auto net_update = m_World->getSingletonComponent<Rtype::NetworkUpdateSingletonComponent>();
    m_World->clearDeferList();
    target.expose().clear(Rtype::color::Black);
    m_World->getSystem<Rtype::MovementUpdateSystem>()->update(delta, m_World);
    m_World->getSystem<RenderSystem>()->update(delta, m_World, target);
    net_update.get()->packets.clear();
}

void MenuScene::lateUpdate(float delta, Rtype::RenderTarget& target)
{ }
