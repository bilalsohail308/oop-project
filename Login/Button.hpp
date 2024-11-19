#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;

    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& label, sf::Font& font, const sf::Color& buttonColor, const sf::Color& textColor);

    bool isClicked(const sf::Vector2i& mousePos) const;
    void draw(sf::RenderWindow& window) const;
};

#endif // BUTTON_H
