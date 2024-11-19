#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <SFML/Graphics.hpp>
#include <string>

class TextInput {
public:
    TextInput(const sf::Vector2f& position, const sf::Vector2f& size, sf::Font& font, const std::string& placeholder = "");

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window) const;
    std::string getText() const;

private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Text placeholderText;
    bool isActive;
};

#endif // TEXT_INPUT_H
