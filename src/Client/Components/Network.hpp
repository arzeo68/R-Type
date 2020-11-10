#pragma once

#include <vector>
#include <utility>
#include <ObserverPattern/Subject.hpp>
#include <Client/unique_id.hpp>
#include <Client/typeEncapsulation.hpp>

enum NetworkEventType {};

class ANetworkComponent {
public:
    virtual ~ANetworkComponent() {}

    virtual void update(NetworkEventType const&, std::shared_ptr<Observer::IEvent>) = 0;

protected:
    uint32_t unique_network_id;
};

class PlayerNetworkComponent : public ANetworkComponent {
public:
    PlayerNetworkComponent(Observer::Subject<NetworkEventType>& subject, std::vector<NetworkEventType> const& listenned, uint32_t unique_id)
        : unique_network_id(unique_id)
    {
        for (auto& event_type : listenned) {
            subject.registerObserver(event_type, std::bind(&PlayerNetworkComponent::update, this, std::placeholders::_1, std::placeholders::_2));
        }
    }

    ~PlayerNetworkComponent() override = default;

    void update(NetworkEventType const& type, std::shared_ptr<Observer::IEvent> data);
};
