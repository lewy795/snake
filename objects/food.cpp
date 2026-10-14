#include "food.h"

void Food::newPosition(sf::Vector2f &pos) {
    if (!freePos.empty()) {
        const int i = rand() % freePos.size();

        pos = freePos[i];
        occupyPos(pos);
    } else {

    }
}

Food::Food(std::string n, int amnt) : name(std::move(n)), amount(amnt) {

    sf::Vector2f newPos;

    for (int i=1; i<=amount; i++) {
        newPosition(newPos);
        pos.push_back(newPos);
    }

    timeSum = 0;

    body.setFillColor(sf::Color(220, 70, 70));
    float rad = (field_width)/2.0f;
    body.setRadius(rad);
}

bool Food::isEaten(sf::Vector2f foodPos) {

    for (sf::Vector2f &head : snakeHeadPos) {
        if (foodPos == head) {
            return true;
        }
    }

    return false;
}

void Food::update(float deltaTime) {
    timeSum += deltaTime;

    if (timeSum >= 1.0f/snakeVelo) {

        for (sf::Vector2f &p : pos) {
            if (isEaten(p)) {
                newPosition(p);
                appleCount++;
                snakeLength++;
            }
        }

        timeSum = 0;
    }
}

void Food::draw(sf::RenderWindow &window) {
    for (sf::Vector2f &p : pos) {
        body.setPosition(p);
        window.draw(body);
    }
}
