#include <SFML/Graphics.hpp>
#include "LoginScreen.hpp"
#include "SignupScreen.hpp"
#include "HomeScreen.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "HU BAZAAR");

    std::string loggedInUser;

    while (window.isOpen()) {
        if (LoginScreen::show(window, loggedInUser)) {
            while (!loggedInUser.empty()) {
                HomeScreen::show(window, loggedInUser);

                loggedInUser.clear(); 
                break; 
            }
        } else {
           
            if (SignupScreen::show(window)) {
                continue;  
            }
        }
    }

    return 0;
}
