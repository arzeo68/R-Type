//
// Created by arzeo on 10/28/2020.
//

#ifndef BABEL_TYPEENCAPSULATION_HPP
#define BABEL_TYPEENCAPSULATION_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace Rtype {
    typedef sf::Vector2i vec2i;
    typedef sf::Vector2f vec2f;
    typedef sf::Vector3f vec3f;
    typedef sf::IntRect iRect;
    typedef sf::FloatRect fRect;
    typedef sf::Color color;

    typedef sf::Keyboard::Key keys;
    typedef sf::Texture Texture;
    typedef sf::Image Image;
    typedef sf::Sprite Sprite;
}  // namespace Rtype

#endif  // BABEL_TYPEENCAPSULATION_HPP
