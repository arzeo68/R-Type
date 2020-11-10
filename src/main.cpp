#include <SFML/Graphics.hpp>
#include <memory>
#include "ECS/World.hpp"

#include "Components/Transform.hpp"
#include "Components/Rectangle.hpp"
#include "Components/Color.hpp"

#include "Systems/RenderSystem.hpp"

#include "ECS/RenderSystem.hpp"
#include "Systems/RenderSystem_1.hpp"

float frand(float low, float high)
{
    return (low + static_cast<float>(rand()) / ( static_cast<float>(RAND_MAX / (high - low))));
}

int main()
{
    /*srand(static_cast<unsigned int>(time(0)));
    std::shared_ptr<ECS::World> world = std::make_shared<ECS::World>();

    world->initialize();

    world->registerComponent<TransformComponent>();
    world->registerComponent<RectangleComponent>();
    world->registerComponent<ColorComponent>();         // Singleton don't need to be registered to system (they must be constant)

    world->addSingletonComponents<ColorComponent>(
        ColorComponent{sf::Color::Blue}
    );

    auto render_sytem1 = world->registerSystem<RenderSystem_Layer1>();
    world->setSystemSignature<RenderSystem_Layer1, TransformComponent, RectangleComponent, LayerComponent_Layer1>();

    auto render_sytem2 = world->registerSystem<RenderSystem_Layer2>();
    world->setSystemSignature<RenderSystem_Layer2, TransformComponent, RectangleComponent, LayerComponent_Layer2>();

    sf::RenderWindow win(sf::VideoMode(1920, 1080), "ECS", sf::Style::Default);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));

    win.setView(view);
    for (int i = 0; i < 2; i += 1) {
        ECS::Entity entity = world->createEntity();

        if (entity % 2 == 0) {
            world->addComponents<TransformComponent, RectangleComponent, LayerComponent_Layer1>(
                entity,
                TransformComponent(sf::Vector2f(0, 0), frand(0, 360), sf::Vector2f(100, 100)),
                RectangleComponent(sf::Color::Red),
                LayerComponent_Layer1{}
            );
        } else {
            world->addComponents<TransformComponent, RectangleComponent, LayerComponent_Layer2>(
                entity,
                TransformComponent(sf::Vector2f(0, 0), frand(0, 360), sf::Vector2f(100, 100)),
                RectangleComponent(sf::Color::Green),
                LayerComponent_Layer2{}
            );
        }
    }

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();
        }
        win.clear();
        render_sytem1->update(0.f, world, win, view.getTransform());
        render_sytem2->update(0.f, world, win, view.getTransform());
        win.display();
    }*/
    return 0;
}