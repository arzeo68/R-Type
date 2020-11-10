#include <SFML/Graphics.hpp>
#include <memory>
#include "ECS/World.hpp"

#include "Systems/RenderSystem.hpp"

#include "Components/Texture.hpp"
#include "Components/Transform.hpp"
#include "Components/Sprite.hpp"

float frand(float low, float high)
{
    return (low + static_cast<float>(rand()) / ( static_cast<float>(RAND_MAX / (high - low))));
}

int main()
{
    std::shared_ptr<ECS::World> world = std::make_shared<ECS::World>();

    world->initialize();

    world->registerComponent<SpriteComponent>();
    world->registerComponent<TextureReferenceComponent>();
    world->registerComponent<TextureLibrarySingletonComponent>();
    world->registerComponent<TransformComponent>();

    world->addSingletonComponents<TextureLibrarySingletonComponent>(
        TextureLibrarySingletonComponent()
    );

    auto render_system = world->registerSystem<RenderSystem>();
    world->setSystemSignature<RenderSystem, SpriteComponent, TransformComponent>();

    TextureLibrarySingletonComponent *tmp = world->getSingletonComponent<TextureLibrarySingletonComponent>().get();

    tmp->add_default_fallback_texture();
    tmp->add_texture("../src/res/Sprite_rtype.png");

    for (int i = 0; i < 1; ++i) {
        ECS::Entity e = world->createEntity();

        world->addComponents<TransformComponent, SpriteComponent, TextureReferenceComponent>(
            e,
            TransformComponent(sf::Vector2f((1920 / 2), (1080 / 2)), 0, sf::Vector2f(1, 1)),
            SpriteComponent(*world->getSingletonComponent<TextureLibrarySingletonComponent>().get(), "Fallback"),
            TextureReferenceComponent(*world->getSingletonComponent<TextureLibrarySingletonComponent>().get(), "Fallback")
        );
    }

    sf::RenderWindow win(sf::VideoMode(1920, 1080), "ECS Test");

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();
        }
        win.clear(sf::Color::Transparent);
        render_system->update(0.f, world, win);
        win.display();
    }

    return 0;
}