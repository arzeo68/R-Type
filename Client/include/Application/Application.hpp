#pragma once

#include <memory>
#include <Client/include/window/IWindow.hpp>
#include <Client/include/SceneManager/SceneManager.hpp>
#include <Client/include/EventManager/EventManager.hpp>

namespace Rtype
{

class Application {
public:
    Application(std::string const& title, unsigned int width, unsigned int height);
    ~Application() = default;

    void addScene(std::string const& title, std::shared_ptr<IScene> scene);
    void removeScene(std::string const& title);
    void switchScene(std::string const& title);

    void run();

private:
    void catch_close(EventType type, std::shared_ptr<Observer::IEvent> data);

private:
    std::shared_ptr<IWindow> m_pWindow;
    std::shared_ptr<SceneManager> m_pSceneManager;
    std::shared_ptr<AEventManager> m_pEventManager;
    std::unordered_map<std::string, unsigned int> m_cScenes;
};

} // namespace Rtype