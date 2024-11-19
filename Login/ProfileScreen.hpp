#ifndef PROFILE_SCREEN_H
#define PROFILE_SCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

class ProfileScreen {
public:
    static void show(sf::RenderWindow& window, const std::string& username);
};

#endif // PROFILE_SCREEN_H
