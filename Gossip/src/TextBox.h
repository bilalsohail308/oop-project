#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class TextBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;
    bool isSelected = false;
    std::string content;
    bool isPassword = false;

public:
    TextBox(float x, float y, float width, float height, const sf::Font& font, bool password = false)
        : font(font), isPassword(password) {
        box.setSize({width, height});
        box.setPosition(x, y);
        box.setFillColor(sf::Color::Black);
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2);

        text.setFont(font);
        text.setPosition(x + 5, y + 5);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
    }

    void handleInput(sf::Event& event) {
        if (isSelected) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {  // Backspace
                    if (!content.empty()) {
                        content.pop_back();
                    }
                } else if (event.text.unicode < 128) {  // Regular characters
                    content += static_cast<char>(event.text.unicode);
                }
            }
        }
    }

    void setSelected(bool selected) {
        isSelected = selected;
        box.setOutlineColor(selected ? sf::Color::Cyan : sf::Color::White);
    }

    bool contains(sf::Vector2f point) const {
        return box.getGlobalBounds().contains(point);
    }

    void render(sf::RenderWindow& window) {
        text.setString(isPassword ? std::string(content.size(), '*') : content);
        window.draw(box);
        window.draw(text);
    }

    std::string getText() const {
        return content;
    }

    void clear() {
        content.clear();
    }
};

#endif