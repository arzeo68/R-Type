//
// Created by arzeo on 10/31/2020.
//

#ifndef BABEL_RENDERTARGET_HPP
#define BABEL_RENDERTARGET_HPP

#include <Client/typeEncapsulation.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ARenderTarget.hpp"
namespace Rtype
{
    class RenderTarget : public ARenderTarget
    {
        public:
        RenderTarget(sf::RenderTarget &target);

        ~RenderTarget() override;

        sf::RenderTarget &expose();

        private:
        sf::RenderTarget &_target;
    };
}

#endif //BABEL_RENDERTARGET_HPP
