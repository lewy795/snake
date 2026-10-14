#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "../objects/world.h"


//=====================================================================
// TEXT CLASS
//=====================================================================

class Text : public GameObject {

    sf::Text text;

    sf::Text::Style textStyle;
    sf::String content;
    sf::Color textColor;
    int fontSize;
    sf::FloatRect textBounds;
    sf::Vector2f textPosition;
    float sumTime;

public:

    Text(const sf::String& content, sf::Vector2f position = sf::Vector2f(0, 0),
        int fontSize = 2, sf::Color color = sf::Color::White,
        sf::Text::Style textStyle = sf::Text::Regular);

    static void ensureFontLoaded();

    void update(float deltaTime = 0) override;

    void changeContent(sf::String newContent);

    void changeColor(sf::Color newColor);

    sf::Vector2f getSize() const;

    void draw(sf::RenderWindow &window) override;

    static bool isFontLoaded;
    static sf::Font* font;
};




//=====================================================================
// BUTTON CLASS
//=====================================================================

enum class ButtonState { IDLE, HOVER, PRESSED };

class Button : public GameObject {
private:
    ButtonState state;
    sf::RectangleShape shape;
    Text text;
    float margin;

    sf::Color idleColor;
    sf::Color hoverColor;

    std::function<void()> onClickAction;

public:
    Button(float x, float y, float margin, const std::string& buttonText,
           int fontSize = 2, sf::Color idle = sf::Color::White, sf::Color hover = sf::Color::Black,
           std::function<void()> callback = nullptr);

    void update(float delta) override;

    void updateButton(const sf::Vector2f &mousePos, bool mousePressed);

    void changeContent(sf::String newContent);

    void checkClick();

    void draw(sf::RenderWindow& window) override;
};