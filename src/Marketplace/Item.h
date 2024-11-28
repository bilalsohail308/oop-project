#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "Utils.h"
class Item {
public:
    static const int BOX_WIDTH = 200;
    static const int BOX_HEIGHT = 250;

    std::string name;
    std::string description;
    std::string owner;
    std::string uniqueId; 
    std::string imagePath;
    std::vector<std::string> imagePaths;
    int price;
    sf::RectangleShape box;
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;

    Item(const std::string& uniqueId, const std::string& name, const std::string& description, int price,const std::vector<std::string>& imagePaths, const std::string& owner = "");
};

#endif // ITEM_H
