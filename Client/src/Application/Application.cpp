#include <iostream>
#include <Client/include/window/Window.hpp>
#include <Client/include/Application/Application.hpp>
#include <Client/include/EventManager/SFMLEvents.hpp>

namespace Rtype
{

Application::Application(std::string const& title, unsigned int width, unsigned int height)
{
    m_pWindow = std::make_shared<Window>(title, width, height);
    m_pSceneManager = std::make_shared<SceneManager>();
    m_pEventManager = std::make_shared<EventManager>(*(std::static_pointer_cast<Window>(m_pWindow)));
    std::cout << "Register 'catch_close' on 'EClose'\n";
    m_pEventManager->getSubject().registerObserver(EClose, std::bind(&Application::catch_close, this, std::placeholders::_1, std::placeholders::_2));
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
    std::shared_ptr<Window> w = std::dynamic_pointer_cast<Window>(m_pWindow);
    m_pWindow->open();
    while (m_pWindow->isOpen()) {
        m_pEventManager->update();
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

} // namespace Rtype
