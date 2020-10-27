//
// Created by alexis on 10/27/2020.
//

#include "Client/include/window/Window.hpp"

Window::Window(std::string name, int width, int height):_name(name), _width(width), _height(height)
{
}

bool Window::open()
{
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(_width, _height), _name);
    return true;
}

bool Window::close()
{
    return false;
}

bool Window::isOpen() const
{
    return _window->isOpen();
}
