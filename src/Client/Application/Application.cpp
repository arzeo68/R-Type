#include <iostream>
#include <thread>
#include <Window/Window.hpp>
#include <Client/Application/Application.hpp>
#include <Client/EventManager/SFMLEvents.hpp>
#include <Common/Network.hpp>
#include <Client/ClientNetwork/TcpNetwork.hpp>
#include <Client/ClientNetwork/UdpNetwork.hpp>

namespace Rtype
{

    void _strcpyC(char *dest, const char *source) {
        #ifdef _WIN32
        strcpy_s(dest, sizeof(dest), source);
        #else
        strcpy(dest, source);
        #endif
    }

Application::Application(std::string const& title, unsigned int width, unsigned int height)
{
    m_pWindow = std::make_shared<Window>(title, width, height);
    m_pSceneManager = std::make_shared<SceneManager>();
    m_pEventManager = std::make_shared<EventManager>(*(std::static_pointer_cast<Window>(m_pWindow)));
    std::cout << "Register 'catch_close' on 'EClose'" << std::endl;
    tcpSocket = std::make_shared<Rtype::TCPBoostSocket>("127.0.0.1", "4242", tcpMessageReceived);
    udpSocket = std::make_shared<Rtype::UDPBoostSocket>("127.0.0.1", "4243", tcpMessageReceived);
    m_pEventManager->getSubject().registerObserver(EClose, std::bind(&Application::catch_close, this, std::placeholders::_1, std::placeholders::_2));
    m_pEventManager->getSubject().registerObserver(EKeyPressed, std::bind(&Application::catch_keyPressed, this, std::placeholders::_1, std::placeholders::_2));
}

void Application::addScene(std::string const& title, std::shared_ptr<IScene> scene)
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
        udpSocket->start_socket();
    });
    //tcpSocket->start_socket();
    //udpSocket->start_socket();
    std::shared_ptr<Window> w = std::dynamic_pointer_cast<Window>(m_pWindow);
    m_pWindow->open();
    while (m_pWindow->isOpen()) {
        m_pEventManager->update();
        w->getNativeHandle().clear(sf::Color::Black);
        w->getNativeHandle().display();
    }
    tcpSocket->shutdown_socket();
    udpSocket->shutdown_socket();
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
    std::cout << "Caught key pressed" << std::endl;
    std::shared_ptr<EventKeyPressed> key = std::dynamic_pointer_cast<EventKeyPressed>(data);
    std::string keyString= std::to_string(key->_key);
    RType::Common::Network::TCPPacket p{RType::Common::Network::g_MagicNumber, key->_key};
    //std::string pack((char *)&p, sizeof(RType::Common::Network::TCPPacket));
    //tcpSocket->write(p);
    udpSocket->write(p);
}
} // namespace Rtype
