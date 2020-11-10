#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
struct TransformComponent {
    sf::Vector2f pos;
    float angle;
    sf::Vector2f scale;

    TransformComponent(sf::Vector2f const& position = {0, 0}, float angle = 0, sf::Vector2f const& scale = {1, 1})
        : pos(position), angle(angle), scale(scale)
    { }
};