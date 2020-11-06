#pragma once

#include <functional>
#include <map>
#include <vector>
#include <utility>

namespace Observer
{

    class IEvent {
    public:
        virtual ~IEvent() {}
    };

    template<typename Event>
    class Subject {
    public:
        Subject() = default;

        template<typename Observer>
        void registerObserver(Event const& event, Observer&& observer)
        {
            m_cObservers[event].push_back(std::forward<Observer>(observer));
        }

        template<typename Observer>
        void registerObserver(Event&& event, Observer&& observer)
        {
            m_cObservers[std::move(event)].push_back(std::forward<Observer>(observer));
        }

        void notify(Event const& event, std::shared_ptr<IEvent> data) const
        {
            for (auto const& obs : m_cObservers.at(event))
                obs(data);
        }

        Subject(Subject const&) = delete;
        Subject& operator=(Subject const&) = delete;

    private:
        std::map<Event, std::vector<std::function<void(std::shared_ptr<IEvent>)>>> m_cObservers;
    };

} // namespace Observer