//
// Created by alexis on 10/27/2020.
//

#ifndef BABEL_WINDOW_HPP
#define BABEL_WINDOW_HPP

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "AWindow.hpp"

class Window: public AWindow
{
    public:
    Window(std::string name = "window", int width = 480, int height = 480);

    bool isOpen() const override;

    public:
    bool open() override;

    bool close() override;

    private:
    std::shared_ptr<sf::RenderWindow> _window = nullptr;
    std::string _name;
    int _width;
    int _height;
};

#endif //BABEL_WINDOW_HPP
