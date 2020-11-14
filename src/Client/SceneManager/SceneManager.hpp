#pragma once

#include <unordered_map>
#include <memory>
#include <Client/RenderTarget/RenderTarget.hpp>
#include <Common/ECS/World.hpp>
#include <Client/ObserverPattern/Subject.hpp>
/**
 * main namespace
 */
namespace Rtype
{
/**
 * enum of the different event type that can be triggerd by the scene
 */
    enum EventSceneSwitchType {
        Switch_to
    };
    /**
     * event triggerd on a scene switch
     */
    class EventSceneSwitch : public Observer::IEvent {
    public:
        EventSceneSwitch(unsigned int id) : sceneID(id) { }

        unsigned int sceneID;
    };
    /**
     * interface of all scene
     */
    class IScene {
    public:
        virtual ~IScene() {}
        /**
         * this function will be called when the scene is create
         */
        virtual void onCreate() = 0;
        /**
         * this function will be called when the scene is destroy
         */
        virtual void onDestroy() = 0;
        /**
         * this function will be called when the scene is activate
         */
        virtual void onActivate() {}
        /**
         * this function will be called when the scene is desactivated
         */
        virtual void onDeactivate() {}
        /**
         * this function will be called at the beginning of each frame on this scene
         * @param delta time that has passed between this frame ans the previous one
         * @param terminal_target render target
         */
        virtual void update(float delta, RenderTarget& terminal_target) {}
        /**
        * this function will be called at the end of each frame on this scene
        * @param delta time that has passed between this frame ans the previous one
        * @param terminal_target render target
        */
        virtual void lateUpdate(float delta, RenderTarget& terminal_target) {}
    };

    class AScene : public IScene {
    public:
        virtual ~AScene() {}
        /**
         * this function will be called when the scene is create
         */
        virtual void onCreate() = 0;
        /**
        * this function will be called when the scene is destroy
        */
        virtual void onDestroy() = 0;
        /**
         * this function will be called when the scene is activate
         */
        virtual void onActivate() {}
        /**
        * this function will be called when the scene is desactivated
        */
        virtual void onDeactivate() {}
        /**
         * this function will be called at the beginning of each frame on this scene
         * @param delta time that has passed between this frame ans the previous one
         * @param terminal_target render target
         */
        virtual void update(float delta, RenderTarget& terminal_target) {}
        /**
        * this function will be called at the end of each frame on this scene
        * @param delta time that has passed between this frame ans the previous one
        * @param terminal_target render target
        */
        virtual void lateUpdate(float delta, RenderTarget& terminal_target) {}
        /**
         * this function return you the subject that you need to register to be informed of any changement on the scene
         * @return the subject
         */
        Observer::Subject<EventSceneSwitchType>& getSubject() { return m_Subject; }
        /**
         * this function allow the user to change scene
         * @param scene the id of the scene on which you want move
         */
        void switch_to(unsigned int scene)
        {
            std::shared_ptr<EventSceneSwitch> event = std::make_shared<EventSceneSwitch>(scene);
            m_Subject.notify(Switch_to, event);
        };
    protected:
        std::shared_ptr<ECS::World> m_World;
        Observer::Subject<EventSceneSwitchType> m_Subject;
    };
    /**
     * this class handle all the scene
     */
    class SceneManager {
    public:
        SceneManager();
        /**
        * this function will call the current scene update at the beginning of each frame on this scene
        * @param delta time that has passed between this frame ans the previous one
        * @param terminal_target render target
        */
        void update(float delta, RenderTarget& terminal_target);
        /**
        * this function will call the current scene update at the end of each frame on this scene
        * @param delta time that has passed between this frame ans the previous one
        * @param terminal_target render target
        */
        void lateUpdate(float delta, RenderTarget& terminal_target);
        /**
         * this function allow the user to add a new scene
         * @param scene a shared pointer on a scene that you want to be added
         * @return the id of the added
         */
        unsigned int add(std::shared_ptr<AScene> scene);
        /**
         * this function switch between the current scene and the scene specified as parameter
         * @param id the id of the scene on which you want move
         */
        void switch_to(unsigned int id);
        /**
         * remove a scene form the scene manager
         * @param id the scene that you want to be removed
         */
        void remove(unsigned int id);

    private:
        void catch_switch(EventSceneSwitchType, std::shared_ptr<Observer::IEvent>);

        std::unordered_map<unsigned int, std::shared_ptr<AScene>> m_cScenes;
        std::shared_ptr<AScene> m_pCurrentScene;
        unsigned int m_nInsertedSceneID;
    };

} // namespace Rtype
