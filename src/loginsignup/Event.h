#ifndef EVENT_H
#define EVENT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class Event {
public:
    std::string name;
    std::string description;
    std::string date;
    std::string venue;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    sf::RectangleShape box;

    static const int BOX_WIDTH = 200;
    static const int BOX_HEIGHT = 250;

    Event(const std::string& name, const std::string& description, const std::string& date, const std::string& venue, const std::string& imagePath);
};

#endif // EVENT_H
