#include <SFML/Graphics.hpp>
#include "MarketplaceScreen.h"
#include "NavBar.h"
#include "AuthScreen.h"
#include "Screen.h"
#include <iostream>
#include <memory>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Marketplace App");
    sf::Font font;

    if (!font.loadFromFile("C:/Users/LENOVO/OneDrive/Desktop/Cpp/project.cpp/Marketplace/Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return -1;
    }

    // Initialize user-related variables
    std::string username, batch, major;
    const std::string userFilePath = "C:/Users/LENOVO/OneDrive/Desktop/Cpp/project.cpp/Marketplace/users.txt"; // File to store user data

    // Show authentication screen
    if (!AuthScreen::loginScreen(window, userFilePath, username, batch, major)) {
        return 0; // Exit if the user closes the login screen
    }

    // Dynamically manage the marketplace screen
    std::unique_ptr<MarketplaceScreen> marketplaceScreen = std::make_unique<MarketplaceScreen>(username);

    NavBar navBar(font);
    Screen currentScreen = MARKETPLACE; // Default to Marketplace screen
    bool isLoggedOut = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Pass events to NavBar for navigation
            navBar.handleEvents(window, event, currentScreen, isLoggedOut);

            // Handle logout functionality
            if (isLoggedOut) {
                // Clear previous session
                username.clear();
                batch.clear();
                major.clear();

                // Show authentication screen again
                if (!AuthScreen::loginScreen(window, userFilePath, username, batch, major)) {
                    return 0; // Exit if user closes login screen
                }

                // Reinitialize the marketplace screen for the new user
                marketplaceScreen = std::make_unique<MarketplaceScreen>(username);
                navBar = NavBar(font); // Reinitialize NavBar to avoid stale state
                currentScreen = MARKETPLACE; // Reset to default screen
                isLoggedOut = false; // Reset logout flag
            }

            // Handle events for the current screen
            switch (currentScreen) {
                case MARKETPLACE:
                    marketplaceScreen->handleEvents(window, event);
                    break;
                case GOSSIP:
                    // Handle Gossip screen events
                    break;
                case EVENTS:
                    // Handle Events screen events
                    break;
                case TICKETING:
                    // Handle Ticketing screen events
                    break;
                case PROFILE:
                    AuthScreen::showProfileScreen(window, username, batch, major);
                    break;
            }
        }

        // Render the current screen
        window.clear(sf::Color::White);
        switch (currentScreen) {
            case MARKETPLACE:
                marketplaceScreen->render(window);
                break;
            case GOSSIP:
                // Render Gossip screen
                break;
            case EVENTS:
                // Render Events screen
                break;
            case TICKETING:
                // Render Ticketing screen
                break;
            case PROFILE:
                AuthScreen::showProfileScreen(window, username, batch, major);
                currentScreen = MARKETPLACE; // Return to Marketplace after viewing the profile
                break;
        }

        // Render navigation bar on top
        navBar.render(window);
        window.display();
    }

    return 0;
}
