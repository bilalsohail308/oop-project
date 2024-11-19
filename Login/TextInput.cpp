#include "TextInput.hpp"

TextInput::TextInput(const sf::Vector2f& position, const sf::Vector2f& size, sf::Font& font, const std::string& placeholder)
    : isActive(false) {
    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(sf::Color(230, 230, 230));

    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(position.x + 5, position.y + 5);
    text.setFillColor(sf::Color::Black);

    placeholderText.setFont(font);
    placeholderText.setCharacterSize(20);
    placeholderText.setPosition(position.x + 5, position.y + 5);
    placeholderText.setFillColor(sf::Color(150, 150, 150));
    placeholderText.setString(placeholder);
}

void TextInput::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        isActive = box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') { // Handle backspace
            if (!text.getString().isEmpty()) {
                std::string currentText = text.getString();
                currentText.pop_back();
                text.setString(currentText);
            }
        } else if (event.text.unicode < 128) { // ASCII input
            text.setString(text.getString() + static_cast<char>(event.text.unicode));
        }
    }
}

void TextInput::draw(sf::RenderWindow& window) const {
    window.draw(box);
    if (text.getString().isEmpty() && !isActive) {
        window.draw(placeholderText);
    } else {
        window.draw(text);
    }
}

std::string TextInput::getText() const {
    return text.getString();
}
