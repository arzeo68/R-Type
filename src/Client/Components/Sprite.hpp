#pragma once

#include <memory>
#include <Client/typeEncapsulation.hpp>

/**
 * @brief
 * Component representating a sprite for the game.
 */
struct SpriteComponent {
    Rtype::Sprite sprite;

    SpriteComponent() = default;

    SpriteComponent(std::shared_ptr<Rtype::Texture>& tex)
        : sprite()
    {
        sprite.setTexture(*tex);
    }
};