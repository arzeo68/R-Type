/**
 * @file EventManager.hpp
 * @brief Contains the class and enum used to create a EventManager
 * @see Observer::Subject
 */
#pragma once

#include <string>
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Client/include/ObserverPattern/Subject.hpp>
#include <Client/include/window/Window.hpp>

/**
 * @namespace Rtype
 * @brief Global project namespace
 */
namespace Rtype
{
    /**
     * @enum EventType
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
     * @interface IEventManager
     * @brief EventManager Interface
     */
    class IEventManager {
    public:
        virtual ~IEventManager() {}

        virtual void update() = 0;
    };

    /**
     * @class EventManager
     * @brief SFML specification of IEventManager
     */
    class EventManager : public IEventManager {
    public:
        /**
         * @brief Construct the EventManager from the Rtype::Window
         * @see Rtype::Window
         */
        EventManager(Rtype::Window& window)
            : m_Window(window.getNativeHandle())
        { }

        ~EventManager() override = default;

        /**
         * @brief Called every frame, process all pending SFMLEvents
         * @see SFMLEvents.hpp
         */
        void update() override;

    private:
        sf::RenderWindow& m_Window;
        Observer::Subject<EventType> m_Subject;
    };

} // namespace Rtype