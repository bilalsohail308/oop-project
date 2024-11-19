// Item.h
#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class Item {
public:
    std::string name;
    std::string description;
    int price;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    sf::RectangleShape box;

    static const int BOX_WIDTH = 200;
    static const int BOX_HEIGHT = 250;

    Item(const std::string& name, const std::string& description, int price, const std::string& imagePath);
};

#endif // ITEM_H
