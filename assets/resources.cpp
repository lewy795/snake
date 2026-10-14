#include "resources.h"
#include <utility>
#include <iostream>

//=====================================================================
// TEXT CLASS
//=====================================================================

sf::Font* Text::font = nullptr;
bool Text::isFontLoaded = false;

void Text::ensureFontLoaded() {
    if (!Text::isFontLoaded) {
        Text::font = new sf::Font();
        std::string fontPath = "assets/Slackey.ttf";

        if (!Text::font->openFromFile(fontPath)) {
            std::cerr << "CRITICAL ERROR: Could not load Slackey.ttf\n";
            std::cerr << "Check if the file exists in assets/ folder." << std::endl;
            exit(1);
        }

        Text::isFontLoaded = true;
    }
}

Text::Text(const sf::String& ctn, sf::Vector2f pos, int fs, sf::Color clr, sf::Text::Style ts)
    : content(ctn),
    textColor(clr),
    textPosition(pos),
    fontSize(fs),
    textStyle(ts),
    text((ensureFontLoaded(), *font), ctn, fs) {

    update();
    sumTime = 0;
}

void Text::update(float deltaTime) {
    text.setFont((ensureFontLoaded(), *font));
    text.setString(content);
    text.setCharacterSize(fontSize);
    text.setFillColor(textColor);
    text.setStyle(textStyle);

    textBounds = text.getLocalBounds();
    text.setOrigin({
        textBounds.size.x / 2.0f,
        textBounds.size.y / 2.0f
    });
    text.setPosition(textPosition);
}

void Text::changeContent(sf::String newContent) {
    content = std::move(newContent);
    text.setString(content);
    update();
}

void Text::changeColor(sf::Color newColor) {
    textColor = newColor;
    text.setFillColor(textColor);
    update();
}

sf::Vector2f Text::getSize() const {
    return textBounds.size;
}

void Text::draw(sf::RenderWindow &window) {
    window.draw(text);
}

//=====================================================================
// BUTTON CLASS
//=====================================================================

Button::Button(float x, float y, float m, const std::string& buttonText,
           int fontSize, sf::Color idle, sf::Color hover,
           std::function<void()> callback)
            : text(buttonText, sf::Vector2f(x, y), fontSize, hover),
            idleColor(idle), hoverColor(hover), margin(m),
            onClickAction(std::move(callback)) {
    state = ButtonState::IDLE;

    sf::Vector2f textSize = text.getSize();
    shape.setSize({textSize.x + margin * 2.f, textSize.y + margin * 1.6f});

    shape.setOrigin({shape.getSize().x / 2.0f, shape.getSize().y / 2.0f});
    shape.setPosition({x, y});
    shape.setFillColor(idle);
    shape.setOutlineColor(hover);
    shape.setOutlineThickness(2);
}

void Button::update(float deltaTime) {

}

void Button::updateButton(const sf::Vector2f& mousePos, bool mousePressed) {
    state = ButtonState::IDLE;

    if (shape.getGlobalBounds().contains(mousePos)) {
        state = ButtonState::HOVER;

        if (mousePressed) {
            state = ButtonState::PRESSED;
        }
    }

    switch (state) {
        case ButtonState::IDLE:
            shape.setFillColor(idleColor);
            break;
        case ButtonState::HOVER:
            shape.setFillColor(hoverColor);
            break;
        case ButtonState::PRESSED:
            shape.setFillColor(sf::Color(100, 100, 100));
            break;
    }
}

void Button::changeContent(sf::String newContent) {
    text.changeContent(std::move(newContent));
}

void Button::checkClick() {
    if (state == ButtonState::PRESSED) {
        onClickAction();
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    text.draw(window);
}