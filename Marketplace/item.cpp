#include "Item.h"
#include <algorithm>
#include "Utils.h"


Item::Item(const std::string& uniqueId,
           const std::string& name,
           const std::string& description,
           int price,
           const std::vector<std::string>& imagePaths,
           const std::string& owner)
    : uniqueId(uniqueId), name(name), description(description), price(price), imagePaths(imagePaths), owner(owner)  { // Initialize image paths
    box.setSize(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
    box.setFillColor(sf::Color(200, 200, 200));

    texture = std::make_shared<sf::Texture>();
    if (!imagePaths.empty() && texture->loadFromFile(imagePaths[0])) { // Load the first image
        sprite.setTexture(*texture);

        float scaleX = (BOX_WIDTH - 20) / static_cast<float>(texture->getSize().x);
        float scaleY = (BOX_HEIGHT - 60) / static_cast<float>(texture->getSize().y);
        float scale = std::min(scaleX, scaleY);
        sprite.setScale(scale, scale);

        float spriteWidth = texture->getSize().x * scale;
        float spriteHeight = texture->getSize().y * scale;
        sprite.setPosition((BOX_WIDTH - spriteWidth) / 2, (BOX_HEIGHT - spriteHeight) / 2 - 20);
    }
}
