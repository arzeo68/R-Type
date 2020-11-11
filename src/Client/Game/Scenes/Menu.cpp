#include <iostream>
#include <Client/Game/Scenes/Menu.hpp>
#include <Client/Components/TextureLibrary.hpp>
#include <Client/Components/Sprite.hpp>


void MenuScene::onCreate()
{
    std::cout << "Creating MenuScene\n";
    m_World = std::make_shared<ECS::World>();
    m_World->initialize();

    m_World->registerComponent<TextureLibraryComponent>();
    m_World->registerComponent<SpriteComponent>();
    m_World->registerComponent<TextureComponent>();

    m_World->addSingletonComponents<TextureLibraryComponent>(
        TextureLibraryComponent()
    );

    auto texlib = m_World->getSingletonComponent<TextureLibraryComponent>();

    texlib.get()->load_default_texture("<default>");
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

void MenuScene::update(float delta, Rtype::RenderTarget& terminal_target)
{ }

void MenuScene::lateUpdate(float delta, Rtype::RenderTarget& terminal_target)
{ }