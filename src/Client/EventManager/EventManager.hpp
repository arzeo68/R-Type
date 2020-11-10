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
#include <ObserverPattern/Subject.hpp>
#include <Window/Window.hpp>

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
        EMouseMoved,
        EKeyPressed
    };

    /**
     * @interface IEventManager
     * @brief EventManager Interface
     */
    class AEventManager {
    public:
        virtual ~AEventManager() {}

        virtual void update() = 0;

        Observer::Subject<EventType>& getSubject() { return m_Subject; }
        Observer::Subject<EventType> const& getSubject() const { return m_Subject; }

    protected:
        Observer::Subject<EventType> m_Subject;
    };

    /**
     * @class EventManager
     * @brief SFML specification of IEventManager
     */
    class EventManager : public AEventManager {
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
    };

} // namespace Rtype
