//
// Created by alexis on 10/27/2020.
//

#include "Window.hpp"

/**
 * @param name window's name
 * @param width window's width
 * @param height window's height
 */
RType::Window::Window(std::string name, int width, int height):_name(name), _width(width), _height(height)
{
}

/**
 *
 * @return open the window
 */
bool RType::Window::open()
{
    _view.setSize({1920, 1080});
    _view.setCenter({0, 0});
    _window.create(sf::VideoMode(_width, _height), _name);
    _window.setView(_view);
    return true;
}

/**
 *
 * @return close the window
 */
bool RType::Window::close()
{
    _window.close();
    return false;
}

/**
 *
 * @return true if the window is open and false if the window is closed
 */
bool RType::Window::isOpen() const
{
    return _window.isOpen();
}

RType::RenderTarget RType::Window::getRenderTarget()
{
    return RenderTarget(_window);
}
