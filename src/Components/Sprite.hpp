#pragma once

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include "Texture.hpp"

struct SpriteComponent {
    SpriteComponent()
        : sprite()
    { }

    SpriteComponent(TextureLibrarySingletonComponent texlib, std::string const& path)
        : sprite()
    {
        sprite.setTexture(texlib.request_texture(path));
    }

    sf::Sprite sprite;
};