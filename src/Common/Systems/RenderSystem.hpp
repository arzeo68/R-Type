#pragma once

#include <SFML/Graphics.hpp>
#include "Common/ECS/System.hpp"
#include "Common/ECS/World.hpp"

#include "Common/Components/Transform.hpp"
#include "Common/Components/Rectangle.hpp"
#include "Common/Components/Color.hpp"

class RenderSystem : public ECS::System {
    public:
        void init();

        void update(float delta, std::shared_ptr<ECS::World>& world, sf::RenderWindow& window, sf::Transform camera);

        typedef std::tuple<const ECS::ComponentHandle<TransformComponent>, ECS::ComponentHandle<RectangleComponent>, const ECS::ComponentHandle<ColorComponent>> Dependencies;

        Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};
