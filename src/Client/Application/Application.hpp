#pragma once

#include <memory>
#include <Window/IWindow.hpp>
#include <Client/SceneManager/SceneManager.hpp>
#include <Client/EventManager/EventManager.hpp>
#include <Client/ClientNetwork/ASocket.hpp>
#include <Common/ECS/World.hpp>

namespace Rtype {

    class Application
    {
    public:
        Application(std::string const& title, unsigned int width,
                    unsigned int height);
        ~Application() = default;

        void addScene(std::string const& title, std::shared_ptr<IScene> scene);
        void removeScene(std::string const& title);
        void switchScene(std::string const& title);

        void run();

    private:
        void catch_close(EventType type,
                         std::shared_ptr<Observer::IEvent> data);
        void catch_keyPressed(EventType type,
                              std::shared_ptr<Observer::IEvent> data);

        void initialize_ecs();

    private:
        std::shared_ptr<std::deque<std::string>> tcpMessageReceived;
        std::shared_ptr<Rtype::ASocket> tcpSocket;
        std::shared_ptr<Rtype::ASocket> udpSocket;
        std::shared_ptr<IWindow> m_pWindow;
        std::shared_ptr<SceneManager> m_pSceneManager;
        std::shared_ptr<AEventManager> m_pEventManager;
        std::unordered_map<std::string, unsigned int> m_cScenes;
        std::shared_ptr<ECS::World> m_World;
    };

}  // namespace Rtype
