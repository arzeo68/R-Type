#pragma once

#include <unordered_map>
#include <memory>
#include <Client/RenderTarget/RenderTarget.hpp>
#include <Common/ECS/World.hpp>
#include <Client/ObserverPattern/Subject.hpp>

namespace Rtype
{

    enum EventSceneSwitchType {
        Switch_to
    };

    class EventSceneSwitch : public Observer::IEvent {
    public:
        EventSceneSwitch(unsigned int id) : sceneID(id) { }

        unsigned int sceneID;
    };

    class IScene {
    public:
        virtual ~IScene() {}

        virtual void onCreate() = 0;
        virtual void onDestroy() = 0;

        virtual void onActivate() {}
        virtual void onDeactivate() {}

        virtual void update(float delta, RenderTarget& terminal_target) {}
        virtual void lateUpdate(float delta, RenderTarget& terminal_target) {}
    };

    class AScene : public IScene {
    public:
        virtual ~AScene() {}

        virtual void onCreate() = 0;
        virtual void onDestroy() = 0;

        virtual void onActivate() {}
        virtual void onDeactivate() {}

        virtual void update(float delta, RenderTarget& terminal_target) {}
        virtual void lateUpdate(float delta, RenderTarget& terminal_target) {}

        Observer::Subject<EventSceneSwitchType>& getSubject() { return m_Subject; }

        void switch_to(unsigned int scene)
        {
            std::shared_ptr<EventSceneSwitch> event = std::make_shared<EventSceneSwitch>(scene);
            m_Subject.notify(Switch_to, event);
        };
    protected:
        std::shared_ptr<ECS::World> m_World;
        Observer::Subject<EventSceneSwitchType> m_Subject;
    };

    class SceneManager {
    public:
        SceneManager();

        void update(float delta, RenderTarget& terminal_target);
        void lateUpdate(float delta, RenderTarget& terminal_target);

        unsigned int add(std::shared_ptr<AScene> scene);
        void switch_to(unsigned int id);
        void remove(unsigned int id);

    private:
        void catch_switch(EventSceneSwitchType, std::shared_ptr<Observer::IEvent>);

        std::unordered_map<unsigned int, std::shared_ptr<AScene>> m_cScenes;
        std::shared_ptr<AScene> m_pCurrentScene;
        unsigned int m_nInsertedSceneID;
    };

} // namespace Rtype
