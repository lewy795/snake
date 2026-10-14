#pragma once
#include <SFML/Graphics.hpp>

inline sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

constexpr int field_width = 40;
constexpr sf::Vector2f field(field_width, field_width);

constexpr int x_fields = 10;
constexpr int y_fields = 6;

constexpr int gameWidth = field.x*x_fields;
constexpr int gameHeight = field.y*y_fields;

inline const unsigned int screenWidth = desktop.size.x;
inline const unsigned int screenHeight = desktop.size.y;
inline const float padding_x = ((float)screenWidth-gameWidth)/2.0f;
inline const float padding_y = ((float)screenHeight-gameHeight)/2.0f;

inline const float centre = (float)screenWidth/2.0f; // by x
inline const float middle = (float)screenHeight/2.0f; // by y

constexpr int fps = 60;

enum class GameMode { GAME, MENU};
inline GameMode mode = GameMode::GAME;

enum class Direction { UP, DOWN, LEFT, RIGHT };

inline float snakeVelo = 5; // 1-20
inline float snakeSpeed = 50; // 0-50

constexpr int startSnakeLength = 3;
inline int snakeLength = startSnakeLength;

inline int appleAmount = 5;
inline int appleCount;

inline std::vector<sf::Vector2f> freePos;
inline std::vector<sf::Vector2f> snakeHeadPos;

inline void clearFreePos() {
    std::vector<sf::Vector2f>().swap(freePos);
}

inline void loadFreePos() {
    for (int i=0; i<(int)x_fields; i++) {
        for (int j=0; j<(int)y_fields; j++) {
            sf::Vector2f newPos(i*field_width+padding_x, j*field_width+padding_y);
            freePos.push_back(newPos);
        }
    }
}

inline void occupyPos(sf::Vector2f pos) {
    for (size_t i = 0; i < freePos.size(); ++i) {
        if (freePos[i] == pos) {
            std::swap(freePos[i], freePos.back());
            freePos.pop_back();
            return;
        }
    }
}