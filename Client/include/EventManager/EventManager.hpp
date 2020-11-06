#pragma once

#include <string>
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Client/include/ObserverPattern/Subject.hpp>
#include <Client/include/window/Window.hpp>

namespace Rtype
{
    /**
     * @brief Generic event types
     */
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

    /**
     * @brief EventManager Interface
     */
    class IEventManager {
    public:
        virtual ~IEventManager() {}

        virtual void update() = 0;
    };

    /**
     * @brief SFML specification of IEventManager
     */
    class EventManager {
    public:
        /**
         * @brief Construct the EventManager from the Rtype::Window
         * @see Rtype::Window
         */
        EventManager(Rtype::Window& window)
            : m_Window(window.getNativeHandle())
        { }

        ~EventManager() = default;

        /**
         * @brief Called every frame, process all pending SFMLEvents
         * @see SFMLEvents.hpp
         */
        void update();

    private:
        sf::RenderWindow& m_Window;
        Observer::Subject<EventType> m_Subject;
    };

} // namespace Rtype