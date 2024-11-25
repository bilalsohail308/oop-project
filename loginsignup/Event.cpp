#include "Event.h"
#include <algorithm>

Event::Event(const std::string& name, const std::string& description, const std::string& date, const std::string& venue, const std::string& imagePath)
    : name(name), description(description), date(date), venue(venue) {
    box.setSize(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
    box.setFillColor(sf::Color(200, 200, 200));

    texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile(imagePath)) {
        sprite.setTexture(*texture);

        float scaleX = (BOX_WIDTH - 20) / static_cast<float>(texture->getSize().x);  //resizing the image by scacel factors to adjust in the box
        float scaleY = (BOX_HEIGHT - 60) / static_cast<float>(texture->getSize().y);
        float scale = std::min(scaleX, scaleY);
        sprite.setScale(scale, scale);

        float spriteWidth = texture->getSize().x * scale;
        float spriteHeight = texture->getSize().y * scale;
        sprite.setPosition((BOX_WIDTH - spriteWidth) / 2, (BOX_HEIGHT - spriteHeight) / 2 - 20);
    }
}
