//
// Created by arzeo on 10/31/2020.
//

#include "Client/include/RenderTarget/RenderTarget.hpp"

RenderTarget::RenderTarget(sf::RenderTarget &target): _target(target)
{
}

void RenderTarget::draw()
{
}

void RenderTarget::clear(Rtype::color color)
{
}

Rtype::vec2i RenderTarget::getSize() const
{
    return Rtype::vec2i();
}
