#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font font;
    std::function<void()> onClick;
    bool isHovered = false;

public:
    Button(float x, float y, float width, float height, const std::string& text, const sf::Font& font)
        : font(font) {
        buttonShape.setSize({width, height});
        buttonShape.setPosition(x, y);
        buttonShape.setFillColor(sf::Color::Green);

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(20);
        buttonText.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = buttonText.getLocalBounds();
        buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, 
                             textBounds.top + textBounds.height / 2.0f);
        buttonText.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    void setOnClick(std::function<void()> func) {
        onClick = func;
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (buttonShape.getGlobalBounds().contains(mousePos)) {
            if (!isHovered) {
                buttonShape.setFillColor(sf::Color::Yellow);
                isHovered = true;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (onClick) onClick();
            }
        } else {
            if (isHovered) {
                buttonShape.setFillColor(sf::Color::Green);
                isHovered = false;
            }
        }
    }

    void render(sf::RenderWindow& window) {
        window.draw(buttonShape);
        window.draw(buttonText);
    }
};

#endif
