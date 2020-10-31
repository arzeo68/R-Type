//
// Created by arzeo on 10/31/2020.
//

#ifndef BABEL_RENDERTARGET_HPP
#define BABEL_RENDERTARGET_HPP

#include <Client/include/typeEncapsulation.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "ARenderTarget.hpp"

class RenderTarget : public ARenderTarget
{

    public:
    RenderTarget(sf::RenderTarget &target);

    void draw() override;

    void clear(Rtype::color color) override;

    Rtype::vec2i getSize() const override;

    private:
    sf::RenderTarget &_target;
};

#endif //BABEL_RENDERTARGET_HPP
