#pragma once

#include <chrono>
#include <SFML/Window/Event.hpp>
#include <Client/include/typeEncapsulation.hpp>
#include <Client/include/ObserverPattern/Subject.hpp>

namespace Rtype
{

class EventClose : public Observer::IEvent {
public:
    EventClose()
    { }

    ~EventClose() = default;

    size_t getMagicCode() const { return typeid(EventClose).hash_code(); }
};

class EventResized : public Observer::IEvent {
public:
    EventResized(unsigned int x, unsigned int y)
        : new_size(x, y)
    { }

    ~EventResized() = default;

    size_t getMagicCode() const { return typeid(EventResized).hash_code(); }

    vec2i new_size;
};

class EventFocus : public Observer::IEvent {
public:
    EventFocus(bool hasFocus)
        : hasFocus(hasFocus)
    { }

    ~EventFocus() = default;

    size_t getMagicCode() const { return typeid(EventFocus).hash_code(); }

    bool hasFocus;
};

class EventText : public Observer::IEvent {
public:
    EventText(uint32_t text)
        : unicode(text)
    { }

    ~EventText() = default;

    size_t getMagicCode() const { return typeid(EventText).hash_code(); }

    uint32_t unicode;
};

class EventMouseWheel : public Observer::IEvent {
public:
    EventMouseWheel(float delta, unsigned int x, unsigned int y)
        : delta(delta), position(x, y)
    { }

    ~EventMouseWheel() = default;

    size_t getMagicCode() const { return typeid(EventMouseWheel).hash_code(); }

    float delta;
    vec2i position;
};

class EventMouseButton : public Observer::IEvent {
public:
    enum State {
        PRESSED,
        RELEASED
    };

    enum Button {
        LEFT,
        RIGHT,
        WHEEL,
        EXTRA
    };

    EventMouseButton(State state, sf::Mouse::Button which, unsigned int x, unsigned int y)
        : state(state), button(LEFT), position(x, y)
    {
        switch (which)
        {
        case sf::Mouse::Button::Left:
            break;
        case sf::Mouse::Button::Right:
            button = RIGHT;
            break;
        case sf::Mouse::Button::Middle:
            button = WHEEL;
            break;
        default:
            button = EXTRA;
            break;
        }
    }

    ~EventMouseButton() = default;

    size_t getMagicCode() const { return typeid(EventMouseButton).hash_code(); }

    State state;
    Button button;
    vec2i position;
};

class EventMouseMove : public Observer::IEvent {
public:
    EventMouseMove(unsigned int x, unsigned int y)
        : position(x, y)
    { }

    ~EventMouseMove() = default;

    size_t getMagicCode() const { return typeid(EventMouseMove).hash_code(); }

    vec2i position;
};

} // namespace Rtype