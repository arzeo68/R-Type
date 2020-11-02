//
// Created by arzeo on 10/31/2020.
//

#ifndef BABEL_RENDERWINDOW_HPP
#define BABEL_RENDERWINDOW_HPP

#include <Client/include/typeEncapsulation.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ARenderTarget.hpp"

class RenderWindow : public ARenderTarget
{
    public:
    RenderWindow();
    ~RenderWindow();

    void draw() override;

    void present() override;

    void clear(Rtype::color color) override;

    Rtype::vec2i getSize() const override;

    private:
    sf::RenderWindow *_window;
};

#endif //BABEL_RENDERWINDOW_HPP
