#include "game.h"
#include <format>

GameCondition game_condition = GameCondition::inGame;

static std::vector<GameObject*> gameWorld;

static float gameTime;

static bool initialized = false;

void cleanupGameWorld() {
    for (GameObject* obj : gameWorld) {
        delete obj;
    }
    gameWorld.clear();
}

void drawCheckerboard(sf::RenderWindow &window) {
    static sf::VertexArray board(sf::PrimitiveType::Triangles, x_fields * y_fields * 6);

    for (int i = 0; i < x_fields; ++i) {
        for (int j = 0; j < y_fields; ++j) {
            sf::Color tileColor = ((i + j) % 2 == 0) ? sf::Color(140, 200, 120) : sf::Color(90, 150, 80);

            float left = i * field_width + padding_x;
            float top = j * field_width + padding_y;
            float right = left + field_width;
            float bottom = top + field_width;

            int index = (i + j * x_fields) * 6;

            board[index + 0] = sf::Vertex{{left, top}, tileColor};
            board[index + 1] = sf::Vertex{{right, top}, tileColor};
            board[index + 2] = sf::Vertex{{left, bottom}, tileColor};

            board[index + 3] = sf::Vertex{{left, bottom}, tileColor};
            board[index + 4] = sf::Vertex{{right, top}, tileColor};
            board[index + 5] = sf::Vertex{{right, bottom}, tileColor};
        }
    }

    window.draw(board);
}

void drawStats(sf::RenderWindow &window) {
    if (!initialized) {
        gameWorld.push_back(new Text("TIME", {(float)screenWidth*0.4f, (float)screenHeight/25.0f}, (float)screenWidth*0.05f, sf::Color(60, 110, 150)));
        gameWorld.push_back(new Text("SCORE", {(float)screenWidth*0.6f, (float)screenHeight/25.0f}, (float)screenWidth*0.05f, sf::Color(60, 110, 150)));
    }

    int minutes = static_cast<int>(gameTime) / 60;
    int seconds = static_cast<int>(gameTime) % 60;

    std::string timeString = std::format("{}:{:02}", minutes, seconds);
    std::string scoreString = std::format("{}", appleCount);

    Text timeText(timeString, {(float)screenWidth*0.4f, (float)screenHeight/8.0f}, (float)screenWidth*0.03f, sf::Color::White);
    Text scoreText(scoreString, {(float)screenWidth*0.6f, (float)screenHeight/8.0f}, (float)screenWidth*0.03f, sf::Color::White);

    timeText.draw(window);
    scoreText.draw(window);
}

void startGame() {

    clearFreePos();
    loadFreePos();

    snakeLength = startSnakeLength;

    gameWorld.push_back(new Snake("snake1"));
    gameWorld.push_back(new Food("apples", appleAmount));
}

void gameOver(sf::RenderWindow &window, std::optional<sf::Event> event) {

    if (!initialized) {
        gameWorld.push_back(new Text("Game Is Over!", {centre, (float)screenHeight/3.0f}, (float)screenWidth*0.1f, sf::Color(220, 70, 70)));
        gameWorld.push_back(new Text("If want to star over again press 'Space'.", {centre, (float)screenHeight/2.0f}, (float)screenWidth*0.02f, sf::Color::White, sf::Text::Italic));
        gameWorld.push_back(new Button(
            centre, 
            middle * 1.2f, 
            (float)screenWidth * 0.03f, 
            "Zagraj ponownie.", 
            static_cast<int>(screenWidth * 0.03f),
            sf::Color::Transparent, 
            sf::Color::White, 
            [] { startGame(); }
        ));
        initialized = true;
    }

    if (event) {
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Space) {
                game_condition = GameCondition::inGame;
                initialized = false;
            }
        }
    }
}

void gameWon(sf::RenderWindow &window, std::optional<sf::Event> event) {

    if (!initialized) {
        gameWorld.push_back(new Text("Congratulations!", {centre, (float)screenHeight/3.0f}, (float)screenWidth*0.1f, sf::Color(140, 200, 120)));
        gameWorld.push_back(new Text("If want to star over again press 'Space'.", {centre, (float)screenHeight/2.0f}, (float)screenWidth*0.02f, sf::Color::White, sf::Text::Italic));
        gameWorld.push_back(new Text("X", {(float)screenWidth*0.96f, (float)screenHeight*0.05f}, (float)screenWidth*0.05f, sf::Color::White));
        initialized = true;
    }

    if (event) {
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Space) {
                game_condition = GameCondition::inGame;
                initialized = false;
            }
        }
    }
}

void inGame(sf::RenderWindow &window, std::optional<sf::Event> event, float deltaTime) {

    if (!initialized) {
        cleanupGameWorld();
        startGame();
        drawStats(window);
        initialized = true;
        gameTime = 0;
    }

    drawStats(window);

    gameTime += deltaTime;

    drawCheckerboard(window);

    for (GameObject* obj : gameWorld) {
        Snake* snake = dynamic_cast<Snake*>(obj);

        if (event) {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (snake != nullptr) {
                    if (keyPressed->code == sf::Keyboard::Key::Up)    snake->changeDirection(Direction::UP);
                    if (keyPressed->code == sf::Keyboard::Key::Right) snake->changeDirection(Direction::RIGHT);
                    if (keyPressed->code == sf::Keyboard::Key::Down)  snake->changeDirection(Direction::DOWN);
                    if (keyPressed->code == sf::Keyboard::Key::Left)  snake->changeDirection(Direction::LEFT);
                }
            }
        }

        if (snake != nullptr) {
            if (snake->hasCollided()) {
                game_condition = GameCondition::Lost;
                initialized = false;
                std::vector<GameObject*>().swap(gameWorld);
                break;
            }
            if (snake->currentLength >= x_fields * y_fields) {
                game_condition = GameCondition::Won;
                initialized = false;
                std::vector<GameObject*>().swap(gameWorld);
                break;
            }
        }

    }
}

void game(sf::RenderWindow &window, std::optional<sf::Event> event, float deltaTime) {
    window.clear(sf::Color(120, 170, 210));

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (game_condition == GameCondition::inGame) inGame(window, event, deltaTime);
    else if (game_condition == GameCondition::Lost) gameOver(window, event);
    else if (game_condition == GameCondition::Won) gameWon(window, event);

    for (GameObject* obj : gameWorld) {
        if (Button* btn = dynamic_cast<Button*>(obj)) {
            btn->updateButton(mousePos, isPressed);

            if (event) {
                if (const auto* released = event->getIf<sf::Event::MouseButtonReleased>()) {
                    if (released->button == sf::Mouse::Button::Left) {
                        btn->checkClick();
                    }
                }
            }
        } else {
            obj->update(deltaTime);
        }
        obj->draw(window);
    }
    window.display();
}