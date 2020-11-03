#pragma once

#include <SFML/Graphics.hpp>

struct RectangleComponent {
    sf::RectangleShape shape;
    sf::Color color;

    RectangleComponent(sf::Color color = sf::Color::White)
        : shape(), color(color)
    {
        shape.setFillColor(color);
        shape.setSize(sf::Vector2f(1, 1));
        shape.setOrigin(sf::Vector2f(0.5, 0.5));
    }
};