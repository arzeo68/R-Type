//
// Created by arzeo on 10/26/2020.
//

#include <iostream>
#include <Client/include/ObserverPattern/Subject.hpp>
#include <Client/include/SceneManager/SceneManager.hpp>
#include <Client/include/ObserverPattern/Subject.hpp>

class EventMessage : public Observer::IEvent {
public:
    EventMessage(std::string const& msg)
        : data(msg)
    { }

    ~EventMessage() = default;

    std::string data;
};

class EventInteger : public Observer::IEvent {
public:
    EventInteger(int value)
        : x(value)
    { }

    ~EventInteger() = default;

    int x;
};

enum EventType {
    Message,
    Integer
};

void simple_callback(std::shared_ptr<Observer::IEvent> event)
{
    std::shared_ptr<EventMessage> message = std::dynamic_pointer_cast<EventMessage>(event);

    std::cout << "Message : " << message->data << "\n";
}

class ObserverIntegerComponent {
public:
    ObserverIntegerComponent(Observer::Subject<EventType>& s, EventType type, int x)
        : x(x)
    { s.registerObserver(type, std::bind(&ObserverIntegerComponent::update, this, std::placeholders::_1)); }

    void update(std::shared_ptr<Observer::IEvent> event)
    {
        std::shared_ptr<EventInteger> integer = std::dynamic_pointer_cast<EventInteger>(event);

        x = integer->x;

        std::cout << x << "\n";
    }

    int x;
};

void testObserverPattern()
{
    Observer::Subject<EventType> s;

    std::cout << "Exemple without a component\n";
    s.registerObserver(Message, std::bind(simple_callback, std::placeholders::_1));

    std::shared_ptr<EventMessage> message = std::make_shared<EventMessage>("Some message send with our new observer pattern");
    s.notify(Message, message);

    std::cout << "Exemple with a component\n";

    ObserverIntegerComponent comp(s, Integer, 10);

    std::shared_ptr<EventInteger> integer = std::make_shared<EventInteger>(10);
    s.notify(Integer, integer);
}

/**
 * @brief
 * Test class for Scene Management
 */
class SceneTest1 : public Rtype::IScene {
public:
        SceneTest1(std::string const& message)
            : message(message)
        { }

        void onCreate() override { std::cout << "onCreate : \"" << message << "\"\n"; }
        void onDestroy() override { std::cout << "onDestroy : \"" << message << "\"\n"; }

        void onActivate() override { std::cout << "onActivate : \"" << message << "\"\n"; }
        void onDeactivate() override { std::cout << "onDeactivate : \"" << message << "\"\n"; }


private:
    std::string message;
};

void SceneTest()
{
    Rtype::SceneManager manager;

    std::shared_ptr<SceneTest1> scene1 = std::make_shared<SceneTest1>("Scene1");
    std::shared_ptr<SceneTest1> scene2 = std::make_shared<SceneTest1>("Scene2");

    unsigned int scene_idx_1 = manager.add(scene1);
    unsigned int scene_idx_2 = manager.add(scene2);

    manager.switch_to(scene_idx_1);

    manager.switch_to(scene_idx_2);

    manager.switch_to(scene_idx_1);

    manager.remove(scene_idx_1);

    manager.remove(scene_idx_2);
}

int main(int argc, char **argv)
{
    std::cout << "-----------------------------------------------------------------------------\n";
    testObserverPattern();
    std::cout << "-----------------------------------------------------------------------------\n";
    SceneTest();
}