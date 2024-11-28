#ifndef AUTHSCREEN_H
#define AUTHSCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

class AuthScreen {
public:
    static bool loginScreen(sf::RenderWindow& window, const std::string& filePath, std::string& username, std::string& batch, std::string& major);
    static void signupScreen(sf::RenderWindow& window, const std::string& filePath);
    static void showProfileScreen(sf::RenderWindow& window, const std::string& username, const std::string& batch, const std::string& major);

private:
    static void showDialogBox(sf::RenderWindow& parentWindow, const std::string& message, const std::string& title);
};

#endif // AUTHSCREEN_H
