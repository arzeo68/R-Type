//
// Created by arzeo on 10/31/2020.
//

#include "Client/include/RenderTarget/RenderWindow.hpp"

RenderWindow::RenderWindow()
{
    _window = new sf::RenderWindow();
}

RenderWindow::~RenderWindow()
{
}

//todo: need to discuss of what we draw to encapsulate that
void RenderWindow::draw()
{
}

void RenderWindow::clear(Rtype::color color)
{
    _window->clear(color);
}

Rtype::vec2i RenderWindow::getSize() const
{
    return Rtype::vec2i(_window->getSize().x, _window->getSize().y);
}

void RenderWindow::present()
{
    _window->display();
}


