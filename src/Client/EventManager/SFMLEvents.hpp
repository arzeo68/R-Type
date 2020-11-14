#pragma once

#include <chrono>
#include <SFML/Window/Event.hpp>
#include <Client/typeEncapsulation.hpp>
#include <ObserverPattern/Subject.hpp>

/**
 * main namespace
 */
namespace Rtype
{
    /**
     * event called when the user close the window
     */
class EventClose : public Observer::IEvent {
public:
    /**
     * constructor
     */
    EventClose()
    { }
    /**
     * destructor
     */
    ~EventClose() = default;
};
    /**
     * event called when the user resize the window
     */
class EventResized : public Observer::IEvent {
public:
    /**
     *
     * @param x new width
     * @param y new heigth
     */
    EventResized(unsigned int x, unsigned int y)
        : new_size(x, y)
    { }

    ~EventResized() = default;

    vec2i new_size;
};
/**
 * event called when the user is focusing the window
 */
class EventFocus : public Observer::IEvent {
public:
    /**
     *
     * @param hasFocus true if the user is focusing the window, otherwise false
     */
    EventFocus(bool hasFocus)
        : hasFocus(hasFocus)
    { }

    ~EventFocus() = default;

    bool hasFocus;
};
    /**
     * event called when the user press a key
     */
class EventKeyPressed : public Observer::IEvent {
    public:
    /**
     *
     * @param key key that is pressed by the user
     */
    EventKeyPressed(keys key)
        : _key(key)
    { }

    ~EventKeyPressed() = default;

    keys _key;
};

/**
 * event called when the user is typing text
 */
class EventText : public Observer::IEvent {
public:
    /**
     *
     * @param input that the user typed
     */
    EventText(uint32_t text)
        : unicode(text)
    { }

    ~EventText() = default;

    uint32_t unicode;
};
    /**
     * event called when the user scroll
     */
class EventMouseWheel : public Observer::IEvent {
public:
    /**
     *
     * @param delta scroll delta
     * @param x mouse x coordinate
     * @param y mouse y coordinate
     */
    EventMouseWheel(float delta, unsigned int x, unsigned int y)
        : delta(delta), position(x, y)
    { }

    ~EventMouseWheel() = default;

    float delta;
    vec2i position;
};
    /**
     * event called when the user click on any mouse button
     */
class EventMouseButton : public Observer::IEvent {
public:
    /**
     * state of the button mouse triggerd
     */
    enum State {
        PRESSED,
        RELEASED
    };
    /**
     * button that trigered the event
     */
    enum Button {
        LEFT,
        RIGHT,
        WHEEL,
        EXTRA
    };
    /**
     *
     * @param state the state of the button mouse triggerd
     * @param which button that trigered the event
     * @param x click x coordinate
     * @param y click y coordinate
     */
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

    State state;
    Button button;
    vec2i position;
};
    /**
     * event called when the user move his mouse
     */
class EventMouseMove : public Observer::IEvent {
public:
    /**
     *
     * @param x new x position
     * @param y new y position
     */
    EventMouseMove(unsigned int x, unsigned int y)
        : position(x, y)
    { }

    ~EventMouseMove() = default;

    vec2i position;
};

} // namespace Rtype
