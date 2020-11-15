#include <iostream>
#include <ratio>
#include <thread>
#include <Window/Window.hpp>
#include <Client/Application/Application.hpp>
#include <Client/EventManager/SFMLEvents.hpp>
#include <Common/Network.hpp>
#include <Client/ClientNetwork/TcpNetwork.hpp>
#include <Client/ClientNetwork/UdpNetwork.hpp>

#include <Client/Game/Scenes/Menu.hpp>

namespace Rtype
{
extern float __aggregated_time = 0.f;

void updateAggregatedTime(float delta) { __aggregated_time += delta; }

float getAggregatedTime(float delta) { return __aggregated_time; }

    void _strcpyC(char *dest, const char *source) {
        #ifdef _WIN32
        strcpy_s(dest, sizeof(dest), source);
        #else
        strcpy(dest, source);
        #endif
    }

Application::Application(std::string const& title, unsigned int width, unsigned int height, const std::string& port)
{
    m_pWindow = std::make_shared<Window>(title, width, height);
    m_pSceneManager = std::make_shared<SceneManager>();
    m_pEventManager = std::make_shared<EventManager>(*(std::static_pointer_cast<Window>(m_pWindow)));
    std::cout << "Register 'catch_close' on 'EClose'" << std::endl;
    tcpMessageReceived = std::make_shared<std::deque<int>>();
    tcpSocket = std::make_shared<Rtype::TCPBoostSocket>("127.0.0.1", "4242", this->_service,
                                                        tcpMessageReceived);
    udpSocket = std::make_shared<Rtype::UDPBoostSocket>("127.0.0.1", "4243", this->_service);
    udpSocket_read = std::make_shared<Rtype::UDPBoostSocket>("127.0.0.1", port, this->_service);
    m_pEventManager->getSubject().registerObserver(EClose, std::bind(&Application::catch_close, this, std::placeholders::_1, std::placeholders::_2));
    m_pEventManager->getSubject().registerObserver(EKeyPressed, std::bind(&Application::catch_keyPressed, this, std::placeholders::_1, std::placeholders::_2));
}

void Application::addScene(std::string const& title, std::shared_ptr<AScene> scene)
{
    unsigned int id = m_pSceneManager->add(scene);
    m_cScenes.insert({title, id});
}

void Application::removeScene(std::string const& title)
{
    auto ite = m_cScenes.find(title);
    if (ite == m_cScenes.end())
        return;
    m_pSceneManager->remove(ite->second);
    m_cScenes.erase(ite);
}

void Application::switchScene(std::string const& title)
{
    auto ite = m_cScenes.find(title);
    if (ite == m_cScenes.end())
        return;
    m_pSceneManager->switch_to(ite->second);
}

void Application::run()
{

    std::thread client_thead([=](){
        tcpSocket->start_socket();
        this->_service.run();
    });

    std::shared_ptr<Window> w = std::dynamic_pointer_cast<Window>(m_pWindow);
    m_pWindow->open();
    auto start = std::chrono::high_resolution_clock::now();
    RenderTarget target = w->getRenderTarget();
    std::shared_ptr<MenuScene> menu = std::make_shared<MenuScene>();
    m_pSceneManager->add(menu);

    while (tcpMessageReceived->empty())
    {
        std::cout << "wait" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    std::cout << "sdfsdf: " << tcpMessageReceived->front() << std::endl;

    while (m_pWindow->isOpen()) {
        udpSocket_read->start_read();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration = end - start;
        float res = duration.count();
        updateAggregatedTime(res);
        m_pEventManager->update();
        m_pSceneManager->update(res, target);
        m_pSceneManager->lateUpdate(res, target);
        // to remove
        w->getNativeHandle().display();
        // --
        start = end;
    }
    tcpSocket->shutdown_socket();
    udpSocket->shutdown_socket();
    udpSocket_read->shutdown_socket();
    this->_service.stop();
    client_thead.join();
}

void Application::catch_close(EventType type, std::shared_ptr<Observer::IEvent> data)
{
    std::cout << "Caught close event\n";
    std::shared_ptr<EventClose> close = std::dynamic_pointer_cast<EventClose>(data);

    m_pWindow->close();
}

void Application::catch_keyPressed(EventType type, std::shared_ptr<Observer::IEvent> data)
{
//    std::cout << "Caught key pressed" << std::endl;
    std::shared_ptr<EventKeyPressed> key = std::dynamic_pointer_cast<EventKeyPressed>(data);
    std::string keyString= std::to_string(key->_key);
    RType::Common::Network::TCPPacket p{RType::Common::Network::g_MagicNumber, key->_key};
//    tcpSocket->write(p);
    udpSocket->write(p);
}

} // namespace Rtype
