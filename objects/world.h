#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void update(float delta) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    sf::Vector2f pos;
};