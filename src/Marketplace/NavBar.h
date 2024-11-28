#ifndef NAVBAR_H
#define NAVBAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Screen.h" // Include the shared Screen enum

class NavBar {
private:
    sf::RectangleShape background;
    std::vector<sf::Text> buttons;
    sf::RectangleShape profileButton;  
    sf::Font font;
    sf::Text profileButtonText;  
    int activeButton;
    sf::RectangleShape logoutButton;
    sf::Text logoutButtonText;


    static const int BUTTON_HEIGHT = 40;
    static const int PADDING = 20;

public:
    NavBar(const sf::Font& font);

    // Handle events like button clicks
    void handleEvents(sf::RenderWindow& window, sf::Event& event, Screen& currentScreen, bool& isLoggedOut);

    // Render the navigation bar
    void render(sf::RenderWindow& window);
};

#endif // NAVBAR_H
