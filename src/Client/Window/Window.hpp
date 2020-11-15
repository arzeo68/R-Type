//
// Created by alexis on 10/27/2020.
//

#ifndef BABEL_WINDOW_HPP
#define BABEL_WINDOW_HPP

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <memory>
#include <Client/RenderTarget/RenderTarget.hpp>
#include "AWindow.hpp"

namespace Rtype
{

    class Window : public AWindow
    {
        public:
        Window(std::string name = "window", int width = 480, int height = 480);

        bool isOpen() const override;

        public:
        bool open() override;

        bool close() override;

        Rtype::RenderTarget getRenderTarget();

        sf::RenderWindow& getNativeHandle() { return _window; }
        sf::RenderWindow const& getNativeHandle() const { return _window; }

        private:
        sf::RenderWindow _window;
        sf::View _view;
        std::string _name;
        int _width;
        int _height;
    };
}

#endif //BABEL_WINDOW_HPP
