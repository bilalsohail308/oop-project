#include "Button.hpp"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& label, sf::Font& font, const sf::Color& buttonColor, const sf::Color& textColor) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(buttonColor);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(textColor);

   
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (size.x - textBounds.width) / 2,
        position.y + (size.y - textBounds.height) / 2 - 5
    );
}

bool Button::isClicked(const sf::Vector2i& mousePos) const {
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(text);
}
