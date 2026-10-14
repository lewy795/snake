#pragma once
#include <SFML/Graphics.hpp>
#include "world.h"
#include "../setup.h"

class Snake : public GameObject {

    std::string name;
    Direction dir;
    Direction next_direction;
    float timeSum;
    std::vector<sf::Vector2f> pos;
    sf::RectangleShape body;
    bool canChangeDirection;

public:
    Snake(std::string name, Direction dir = Direction::RIGHT, sf::Vector2f pos = sf::Vector2f(((float)x_fields/2)*field.x+padding_x, ((float)y_fields/2)*field.y+padding_y));
    bool hasCollided();
    void changeDirection(Direction dir);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow &window) override;

    sf::Vector2f *head;

    int currentLength;
};