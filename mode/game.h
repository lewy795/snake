#pragma once
#include <SFML/Graphics.hpp>
#include "../objects/snake.h"
#include "../objects/food.h"
#include "../setup.h"
#include "../assets/resources.h"

enum class GameCondition {inGame, Lost, Won};

void startGame();

void drawCheckerboard(sf::RenderWindow &window);

void drawStats(sf::RenderWindow &window, float gT);

void game(sf::RenderWindow &window, std::optional<sf::Event> event, float deltaTime);

void inGame(sf::RenderWindow &window, std::optional<sf::Event> event, float deltaTime);

void gameOver(sf::RenderWindow &window, std::optional<sf::Event> event);

void gameWon(sf::RenderWindow &window, std::optional<sf::Event> event);