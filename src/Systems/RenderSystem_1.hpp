#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECS/System.hpp"
#include "ECS/World.hpp"

#include "Components/Transform.hpp"
#include "Components/Rectangle.hpp"
#include "Components/Color.hpp"

#include "ECS/RenderSystem.hpp"

DEFINE_NEW_LAYER(1);
DEFINE_LAYERED_RENDER_SYSTEM(
    1, // -> Name of the Layer
    PROTECT(std::tuple<const ECS::ComponentHandle<TransformComponent>, ECS::ComponentHandle<RectangleComponent>, const ECS::ComponentHandle<ColorComponent>>) // -> Tuple used to retrive data
);

void RenderSystem_1::init()
{
    std::cout << "Init render system 1\n";
}

RenderSystem_1::Dependencies RenderSystem_1::getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
{
    auto const transform = world->getComponent<TransformComponent>(entity);
    auto rectangle = world->getComponent<RectangleComponent>(entity);
    auto color = world->getSingletonComponent<ColorComponent>();

    return std::make_tuple(transform, rectangle, color);
}
