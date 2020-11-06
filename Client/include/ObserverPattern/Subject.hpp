/**
 * @file Subject.hpp
 * @brief Contains our Observer Pattern implementation
 */
#pragma once

#include <functional>
#include <map>
#include <vector>
#include <utility>

/**
 * @namespace Observer
 * @brief Contains the Observer pattern
 */
namespace Observer
{

    /**
     * @interface IEvent
     * @brief Interface used to represent any type of events send using the Observer Pattern
     */
    class IEvent {
    public:
        virtual ~IEvent() {}
    };

    /**
     * @class Subject
     *
     * @brief This class is the heart of the Observer Pattern, it register object to Events and notify them when an event is raised
     *
     * @tparam Event the type used to describe events (usually a enum)
     */
    template<typename Event>
    class Subject {
    public:
        Subject() = default;

        /**
         * @brief Register a observer to this subject
         *
         * @tparam The Observer type m_cObservers for more info on types
         *
         * @param event [in] describe the event on which we are registering the observer
         *
         * @param observer [in] perfect forwarded std::function m_cObservers
         *
         * @see m_cObservers
         */
        template<typename Observer>
        void registerObserver(Event const& event, Observer&& observer)
        {
            m_cObservers[event].push_back(std::forward<Observer>(observer));
        }

        /**
         * @brief Register a observer to this subject
         *
         * @tparam The Observer type m_cObservers for more info on types
         *
         * @param event [in] describe the event on which we are registering the observer
         *
         * @param observer [in] perfect forwarded std::function m_cObservers
         *
         * @see m_cObservers
         */
        template<typename Observer>
        void registerObserver(Event&& event, Observer&& observer)
        {
            m_cObservers[std::move(event)].push_back(std::forward<Observer>(observer));
        }

        /**
         * @brief notify all Observers register to this event
         *
         * @param event [in] describe the event
         *
         * @param data [in] pointer to the event data
         */
        void notify(Event const& event, std::shared_ptr<IEvent> data) const
        {
            for (auto const& obs : m_cObservers.at(event))
                obs(data);
        }

        /**
         * @brief delete
         */
        Subject(Subject const&) = delete;

        /**
         * @brief delete
         */
        Subject& operator=(Subject const&) = delete;

    private:
        /**
         * @brief Map a event to a vector of function. Each function takes a std::shared_ptr<IEvent> as argument (it will contain event data)
         */
        std::map<Event, std::vector<std::function<void(std::shared_ptr<IEvent>)>>> m_cObservers;
    };

} // namespace Observer