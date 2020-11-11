#pragma once

#include <Common/ECS/World.hpp>
#include <Client/RenderTarget/IRenderTarget.hpp>

#include <Client/Components/MonitorComponent.hpp>

class TestSystem : public ECS::System {
public:
    void init();

    typedef std::tuple<ECS::ComponentHandle<MonitorComponent>> Dependencies;

    void update(float delta, std::shared_ptr<ECS::World>& world)
    {
        for (auto const& entity : m_cEntities) {
            auto [ monitor ] = getDependencies(entity, world);

            std::cout << "Frametime : " << delta << " | LastFrame time : " << monitor.get()->frametime << "\n";
            monitor.get()->frametime = delta;
        }
    }

    Dependencies getDependencies(ECS::Entity entity, std::shared_ptr<ECS::World>& world)
    {
        auto monitor = world->getComponent<MonitorComponent>(entity);

        return std::make_tuple(monitor);
    }
};