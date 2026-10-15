#include <SFML/Graphics.hpp>
#include <optional>
#include <filesystem>
#include <iostream>
#include "mode/game.h"
#include "mode/menu.h"

// Sparkle jest dostępne tylko na macOS
#ifdef __APPLE__
#include "updater.h"
#endif

void fixWorkingDirectory(const char* argv0) {
    if (!argv0) return;

    std::filesystem::path exePath = std::filesystem::weakly_canonical(argv0);
    std::filesystem::path resourcesPath = exePath.parent_path().parent_path() / "Resources";

    if (std::filesystem::exists(resourcesPath / "assets")) {
        std::filesystem::current_path(resourcesPath);
    } 
    else if (std::filesystem::exists(exePath.parent_path() / "assets")) {
        std::filesystem::current_path(exePath.parent_path());
    }
}

int main(int argc, char* argv[]) {
    fixWorkingDirectory(argv[0]);

#ifdef __APPLE__
    checkGameUpdates();
#endif

    sf::RenderWindow window(sf::VideoMode({screenWidth, screenHeight}), "Snake");
    window.setFramerateLimit(fps);

    sf::Clock clock;

    while (window.isOpen()) {
        std::optional<sf::Event> currentEvent;

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
                currentEvent = event;
            }
        }

        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        if (mode == GameMode::MENU) {
            menu(window);
        }
        else if (mode == GameMode::GAME) {
            game(window, currentEvent, deltaTime);
        }
    }

    return 0;
}