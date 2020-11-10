#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include "ECS/World.hpp"
#include "ECS/System.hpp"

#define PROTECT(...) __VA_ARGS__

#define DEFINE_NEW_LAYER(name)                          \
    struct LayerComponent_##name {                      \
        static constexpr char *LayerName = #name;       \
    };

#define DEFINE_LAYERED_RENDER_SYSTEM(name, dependency_tuple)                                            \
    class RenderSystem_##name : public ECS::System {                                                    \
    public:                                                                                             \
        void init();                                                                                    \
        void update(float delta, std::shared_ptr<ECS::World>& world, sf::RenderWindow& window);         \
        typedef dependency_tuple Dependencies;                                                          \
        Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world);           \
    };

#define ADD_LAYERED_RENDERSYSTEM(world, name, ...)                                                                                          \
    world->registerSystem<RenderSystem_##name>();                                                                                           \
    world->setSystemSignature<RenderSystem_##name, __VA_ARGS__, LayerComponent_##name>();
