#pragma once

#include <memory>
#include <Client/typeEncapsulation.hpp>
#include <iostream>

/**
 * @brief
 * Component representating a sprite for the game.
 */
struct SpriteComponent {
    std::shared_ptr<RType::sfmlSprite> sprite;

    SpriteComponent() = default;

    SpriteComponent(std::shared_ptr<RType::ITexture<RType::Texture>> tex, RType::iRect *base)
    {
        sprite = std::make_shared<RType::sfmlSprite>();
        sprite->setTexture(tex->getNativ());
        if (base != 0)
            sprite->setTextureRect(*base);
        sprite->centerOrigin();
    }
};