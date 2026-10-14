#pragma once
#include <SFML/Graphics.hpp>
#include "world.h"
#include "snake.h"


class Food : public GameObject {
    std::string name;
    int amount;
    float timeSum;
    sf::CircleShape body;

public:
    static void newPosition(sf::Vector2f &pos);
    Food(std::string name, int amount);
    static bool isEaten(sf::Vector2f foodPos);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow &window) override;

    std::vector<sf::Vector2f> pos;
};
