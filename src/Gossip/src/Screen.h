#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

// Abstract base class for screens
class Screen {
public:
    virtual void handleInput(sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~Screen() = default;
};

#endif