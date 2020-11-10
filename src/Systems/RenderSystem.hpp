#pragma once

#include <SFML/Graphics.hpp>
#include "ECS/System.hpp"
#include "ECS/World.hpp"

#include "Components/Transform.hpp"
#include "Components/Sprite.hpp"
#include "Components/Texture.hpp"

class RenderSystem : public ECS::System {
    public:
        void init();

        void update(float delta, std::shared_ptr<ECS::World>& world, sf::RenderWindow& window);

        typedef std::tuple<const ECS::ComponentHandle<SpriteComponent>, const ECS::ComponentHandle<TransformComponent>> Dependencies;

        Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);
};