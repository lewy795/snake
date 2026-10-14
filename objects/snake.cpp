#include "snake.h"

#include <utility>

Snake::Snake(std::string n, Direction d, sf::Vector2f headPos) : name(std::move(n)), dir(d) {

    timeSum = 0;
    next_direction = dir;
    canChangeDirection = true;

    pos.clear();
    pos.push_back(headPos);
    head = &pos.back();

    occupyPos(headPos);

    currentLength = 1;

    body.setFillColor(sf::Color(230, 130, 170));
    sf::Vector2f bodySize(field.x, field.y);
    body.setSize(bodySize);
}

bool Snake::hasCollided() {

    sf::Vector2f headPos = pos.back();

    if (headPos.x < padding_x || headPos.x > gameWidth - field.x + padding_x ||
        headPos.y < padding_y || headPos.y > gameHeight - field.y + padding_y) {
        return true;
        }

    body.setPosition(headPos);
    sf::FloatRect headBounds = body.getGlobalBounds();

    for (int i = 0; i < (int)pos.size() - 2; i++) {
        sf::RectangleShape tempBody = body;
        tempBody.setPosition(pos[i]);

        if (headBounds.findIntersection(tempBody.getGlobalBounds()).has_value()) {
            return true;
        }
    }
    return false;
}

void Snake::changeDirection(Direction nd) {
    next_direction = nd;

    if (((dir == Direction::RIGHT || dir == Direction::LEFT)
        && (next_direction == Direction::RIGHT || next_direction == Direction::LEFT))
            ||((dir == Direction::DOWN || dir == Direction::UP)
                && (next_direction == Direction::DOWN || next_direction == Direction::UP))) return;

    if (static_cast<int> (head->x - padding_x) % field_width == 0 && static_cast<int> (head->y - padding_y) % field_width == 0 && canChangeDirection) {
        dir = next_direction;
    }

    canChangeDirection = false;
}

void Snake::update(float deltaTime) {

    timeSum += deltaTime;

    if (timeSum >= 1.0f/snakeVelo) {

        sf::Vector2f newHeadPos = pos.back();

        switch (dir) {
            case Direction::UP:    newHeadPos.y -= field_width; break;
            case Direction::RIGHT: newHeadPos.x += field_width; break;
            case Direction::DOWN:  newHeadPos.y += field_width; break;
            case Direction::LEFT:  newHeadPos.x -= field_width; break;
        }

        pos.push_back(newHeadPos);

        if (snakeHeadPos.size() > 0) {
            snakeHeadPos.pop_back();
        }

        snakeHeadPos.push_back(newHeadPos);

        occupyPos(newHeadPos);

        head = &pos.back();

        if (pos.size() > snakeLength) {

            freePos.push_back(pos.front());

            pos.erase(pos.begin());
        }

        currentLength = pos.size();

        canChangeDirection = true;

        timeSum = 0;
    }
}

void Snake::draw(sf::RenderWindow &window) {
    for (sf::Vector2f &p : pos) {
        body.setPosition(p);
        window.draw(body);
    }
}