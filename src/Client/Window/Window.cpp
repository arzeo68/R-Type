//
// Created by alexis on 10/27/2020.
//

#include "Window.hpp"

/**
 * @param name window's name
 * @param width window's width
 * @param height window's height
 */
Rtype::Window::Window(std::string name, int width, int height):_name(name), _width(width), _height(height)
{
}

/**
 *
 * @return open the window
 */
bool Rtype::Window::open()
{
    _window.create(sf::VideoMode(_width, _height), _name);
    return true;
}

/**
 *
 * @return close the window
 */
bool Rtype::Window::close()
{
    _window.close();
    return false;
}

/**
 *
 * @return true if the window is open and false if the window is closed
 */
bool Rtype::Window::isOpen() const
{
    return _window.isOpen();
}

Rtype::RenderTarget Rtype::Window::getRenderTarget()
{
    return RenderTarget(_window);
}
