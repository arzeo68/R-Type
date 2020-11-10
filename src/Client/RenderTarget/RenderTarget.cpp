//
// Created by arzeo on 10/31/2020.
//

#include "RenderTarget.hpp"

namespace Rtype
{
    RenderTarget::~RenderTarget()
    {
    }

    RenderTarget::RenderTarget(sf::RenderTarget &target) : _target(target)
    {
    }

    sf::RenderTarget &RenderTarget::expose()
    {
        return _target;
    }
}


