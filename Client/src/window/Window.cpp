//
// Created by alexis on 10/27/2020.
//

#include "Client/include/window/Window.hpp"

/**
 * @param name window's name
 * @param width window's width
 * @param height window's height
 */
Window::Window(std::string name, int width, int height):_name(name), _width(width), _height(height)
{
}

/**
 *
 * @return open the window
 */
bool Window::open()
{
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(_width, _height), _name);
    return true;
}

/**
 *
 * @return close the window
 */
bool Window::close()
{
    return false;
}

/**
 *
 * @return true if the window is open and false if the window is closed
 */
bool Window::isOpen() const
{
    return _window->isOpen();
}
