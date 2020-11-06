#pragma once

#include <string>
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Client/include/ObserverPattern/Subject.hpp>
#include <Client/include/window/Window.hpp>

namespace Rtype
{

    enum EventType {
        EClose,
        EResize,
        ELostFocus,
        EGainedFocus,
        ETextEntered,
        EMouseWheelScrool,
        EMouseButtonPressed,
        EMouseButtonReleased,
        EMouseMoved
    };

    class IEventManager {
    public:
        virtual ~IEventManager() {}

        virtual void update() = 0;
    };

    class EventManager {
    public:
        EventManager(Rtype::Window& window)
            : m_Window(window.getNativeHandle())
        { }

        ~EventManager() = default;

        void update();

    private:
        sf::RenderWindow& m_Window;
        Observer::Subject<EventType> m_Subject;
    };

} // namespace Rtype