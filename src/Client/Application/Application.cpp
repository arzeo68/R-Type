#include <iostream>
#include <Window/Window.hpp>
#include <Client/Application/Application.hpp>
#include <Client/EventManager/SFMLEvents.hpp>
#include <Common/Network.hpp>
#include <Client/ClientNetwork/TcpNetwork.hpp>
#include <Client/ClientNetwork/UdpNetwork.hpp>
#include <Client/Components/TextureLibrary.hpp>
#include <Client/Components/MonitorComponent.hpp>
#include <Client/Systems/TestSystem.hpp>

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
    m_World = std::make_shared<ECS::World>();
    std::cout << "Register 'catch_close' on 'EClose'" << std::endl;
    tcpSocket = std::make_shared<Rtype::TCPBoostSocket>("127.0.0.1", "4242", tcpMessageReceived);
    udpSocket = std::make_shared<Rtype::UDPBoostSocket>("127.0.0.1", "4242", tcpMessageReceived);
    m_pEventManager->getSubject().registerObserver(EClose, std::bind(&Application::catch_close, this, std::placeholders::_1, std::placeholders::_2));
    m_pEventManager->getSubject().registerObserver(EKeyPressed, std::bind(&Application::catch_keyPressed, this, std::placeholders::_1, std::placeholders::_2));
}

void Application::initialize_ecs_components(std::vector<std::pair<std::string, std::string>> const& textures)
{
    m_World->initialize();

    m_World->registerComponent<TextureLibraryComponent>();
    m_World->registerComponent<TextureComponent>();
    m_World->registerComponent<MonitorComponent>();

    m_World->addSingletonComponents<TextureLibraryComponent>(
        TextureLibraryComponent()
    );

    auto texlib = m_World->getSingletonComponent<TextureLibraryComponent>();

    texlib.get()->load_default_texture("<default>");
    for (auto t : textures) {
        texlib.get()->load_texture(t.first, t.second);
    }
}

void Application::initialize_ecs_systems()
{
    m_World->registerSystem<TestSystem>();
    m_World->setSystemSignature<TestSystem, MonitorComponent>();
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
    initialize_ecs_components({});
    initialize_ecs_systems();
    auto e = m_World->createEntity();

    m_World->addComponent<MonitorComponent>(e, MonitorComponent());
    tcpSocket->start_socket();
    udpSocket->start_socket();
    std::shared_ptr<Window> w = std::dynamic_pointer_cast<Window>(m_pWindow);
    m_pWindow->open();
    while (m_pWindow->isOpen()) {
        m_pEventManager->update();
        m_World->getSystem<TestSystem>()->update(0.f, m_World);
        w->getNativeHandle().clear(sf::Color::Black);
        w->getNativeHandle().display();
    }
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
    RType::Common::Network::TCPPacket p{RType::Common::Network::g_MagicNumber};
    _strcpyC(p.message, keyString.c_str());
    //std::string pack((char *)&p, sizeof(RType::Common::Network::TCPPacket));
    tcpSocket->write(p);
//    udpSocket->write(p);
}
} // namespace Rtype
