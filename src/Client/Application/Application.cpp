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

namespace RType
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
    //tcpMessageReceived = std::make_shared<std::deque<int>>();
    tcpMessageReceived = std::make_shared<RType::Network::ThreadSafeQueue<int>>();
    tcpSocket = std::make_shared<RType::TCPBoostSocket>("127.0.0.1", "4242", this->_service,
                                                        tcpMessageReceived->shared_from_this());
    udpSocket = std::make_shared<RType::UDPBoostSocket>("127.0.0.1", "4243", this->_service, std::bind(&Application::catch_network_event, this, std::placeholders::_1, std::placeholders::_2));
    udpSocket_read = std::make_shared<RType::UDPBoostSocket>("127.0.0.1", port, this->_service, std::bind(&Application::catch_network_event, this, std::placeholders::_1, std::placeholders::_2));
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
    menu->register_network(m_subject);
    m_pSceneManager->add(menu);

    while (tcpMessageReceived->empty());
    _networkID = tcpMessageReceived->pop();

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
    std::shared_ptr<EventKeyPressed> key = std::dynamic_pointer_cast<EventKeyPressed>(data);
    std::string keyString= std::to_string(key->_key);
    RType::Common::Network::UDPPacket p{RType::Common::Network::g_MagicNumber, _networkID ,key->_key};
    udpSocket->write(&p, sizeof(p));
}

void Application::catch_network_event(packageType type, std::shared_ptr<Observer::IEvent> data)
{
    std::shared_ptr<NetworkEvent> event = std::dynamic_pointer_cast<NetworkEvent>(data);

    m_subject.notify(type, data);
}

} // namespace RType
