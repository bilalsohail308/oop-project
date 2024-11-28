#include "HomeScreen.hpp"
#include "Button.hpp"
#include "ProfileScreen.hpp"

#include <iostream>

void HomeScreen::show(sf::RenderWindow &window, const std::string &username)
{
    sf::Font font;
    if (!font.loadFromFile("Marketplace/Arial.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    sf::Text title("Home Screen", font, 30);
    title.setPosition(300, 50);

    Button profileButton({250, 150}, {150, 40}, "Profile", font, sf::Color::Blue, sf::Color::White);
    Button marketplaceButton({250, 250}, {150, 40}, "Marketplace", font, sf::Color::Green, sf::Color::White);
    Button logoutButton({250, 350}, {150, 40}, "Logout", font, sf::Color::Red, sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (profileButton.isClicked(mousePos))
                {
                    ProfileScreen::show(window, username); // Pass username to ProfileScreen
                }

                // if (marketplaceButton.isClicked(mousePos))
                // {
                //     Marketplace::show(window); // Open Marketplace
                // // }

                if (logoutButton.isClicked(mousePos))
                {
                    return; // Log out and return to LoginScreen
                }
            }
        }

        window.clear();
        window.draw(title);
        profileButton.draw(window);
        marketplaceButton.draw(window);
        logoutButton.draw(window);
        window.display();
    }
}
