#pragma once

#include <memory>
#include <Client/typeEncapsulation.hpp>
#include <iostream>

/**
 * @brief
 * Component representating a sprite for the game.
 */
struct SpriteComponent {
    std::shared_ptr<Rtype::sfmlSprite> sprite;

    SpriteComponent() = default;

    SpriteComponent(std::shared_ptr<Rtype::ITexture<Rtype::Texture>> tex, Rtype::iRect *base)
    {
        sprite = std::make_shared<Rtype::sfmlSprite>();
        sprite->setTexture(tex->getNativ());
        if (base != 0)
            sprite->setTextureRect(*base);
        sprite->centerOrigin();
    }
};