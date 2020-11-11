#include <iostream>
#include <Client/Game/Scenes/Menu.hpp>
#include <Client/Components/TextureLibrary.hpp>
#include <Client/Components/Sprite.hpp>
#include <Client/Components/Rotation.hpp>
#include <Common/Component/Transform.hpp>

#include <Client/Game/Systems/RenderSystem.hpp>
#include <Client/Game/Systems/RotationSystem.hpp>

void MenuScene::onCreate()
{
    std::cout << "Creating MenuScene\n";
    m_World = std::make_shared<ECS::World>();
    m_World->initialize();

    m_World->registerComponent<TextureLibraryComponent>();
    m_World->registerComponent<SpriteComponent>();
    m_World->registerComponent<TextureComponent>();
    m_World->registerComponent<Rtype::TransformComponent>();
    m_World->registerComponent<RotationComponent>();

    m_World->addSingletonComponents<TextureLibraryComponent>(
        TextureLibraryComponent()
    );

    m_World->registerSystem<RenderSystem>();
    m_World->setSystemSignature<RenderSystem, SpriteComponent, Rtype::TransformComponent>();

    m_World->registerSystem<RotationSystem>();
    m_World->setSystemSignature<RotationSystem, RotationComponent, Rtype::TransformComponent>();

    auto texlib = m_World->getSingletonComponent<TextureLibraryComponent>();

    texlib.get()->load_default_texture("../ressources/default.png");

    ECS::Entity e = m_World->createEntity();

    m_World->addComponents<SpriteComponent, Rtype::TransformComponent, RotationComponent>(
        e,
        SpriteComponent(texlib.get()->get_texture("<default>")),
        Rtype::TransformComponent({1920 / 2, 1080 / 2}, 0, {1, 1}),
        RotationComponent(0.01f)
    );

    std::cerr << "Creating Scene with :\n";
    std::cerr << "\t" << texlib.get()->TextureMap.size() << " textures\n";
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
    m_World->getSystem<RotationSystem>()->update(delta, m_World);
    m_World->getSystem<RenderSystem>()->update(delta, m_World, target);
}

void MenuScene::lateUpdate(float delta, Rtype::RenderTarget& target)
{ }