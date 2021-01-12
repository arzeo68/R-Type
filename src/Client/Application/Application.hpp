#pragma once

#include <boost/asio.hpp>
#include <utility>
#include <memory>
#include <Window/IWindow.hpp>
#include <Client/SceneManager/SceneManager.hpp>
#include <Client/EventManager/EventManager.hpp>
#include <Client/ClientNetwork/ASocket.hpp>
#include <Client/ClientNetwork/UdpNetwork.hpp>
#include "Server/Network/Worker/ThreadSafeQueue.hpp"

namespace RType {

    extern float __aggregated_time;

    class Application
    {
    public:
        Application(std::string const& title, unsigned int width,
                    unsigned int height, const std::string& port);
        ~Application() = default;

        void addScene(std::string const& title, std::shared_ptr<AScene> scene);
        void removeScene(std::string const& title);
        void switchScene(std::string const& title);

        void run();

    private:
        void catch_close(EventType type,
                         std::shared_ptr<Observer::IEvent> data);
        void catch_keyPressed(EventType type,
                              std::shared_ptr<Observer::IEvent> data);

        void catch_network_event(RType::packageType, std::shared_ptr<Observer::IEvent> data);

    private:
        std::shared_ptr<RType::Network::ThreadSafeQueue<int>> tcpMessageReceived;
        std::shared_ptr<RType::ASocket> tcpSocket;
        std::shared_ptr<RType::ASocket> udpSocket;
        std::shared_ptr<RType::ASocket> udpSocket_read;
        std::shared_ptr<IWindow> m_pWindow;
        std::shared_ptr<SceneManager> m_pSceneManager;
        std::shared_ptr<AEventManager> m_pEventManager;
        std::unordered_map<std::string, unsigned int> m_cScenes;
        boost::asio::io_service _service;
        Observer::Subject<RType::packageType> m_subject;
        int _networkID = -1;
    };

}  // namespace RType
