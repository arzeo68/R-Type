#pragma once

#include <SFML/Graphics/Texture.hpp>

/**
 * @brief
 * The texture can be a raw pointer because it can only be used by one rendering thread.
 *
 * Pulling a texture will also most likely be constant
 */
struct TextureComponent {
    sf::Texture *texture;
};