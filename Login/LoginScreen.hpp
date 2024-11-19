#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

class LoginScreen {
public:
    static bool show(sf::RenderWindow& window, std::string& loggedInUser);
};

#endif // LOGIN_SCREEN_H
