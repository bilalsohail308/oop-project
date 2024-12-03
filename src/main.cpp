#include <SFML/Graphics.hpp>
#include "../include/MarketplaceScreen.h"
#include "../include/NavBar.h"
#include "../include/AuthScreen.h"
#include "../include/Screen.h"
#include "../include/EventScreen.h"
#include "../include/gossip.h"
#include <iostream>
#include <memory>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "HU Bazaar");
    sf::Font font;

    if (!font.loadFromFile("F:\\sem3\\OOP\\oop-project\\assets\\Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return -1;
    }

    // Initialize user-related variables
    std::string username, batch, major;
    const std::string userFilePath = "F:\\sem3\\OOP\\oop-project\\assets\\users.txt"; // File to store user data

    // Show authentication screen
    if (!AuthScreen::loginScreen(window, userFilePath, username, batch, major)) {
        return 0; // Exit if the user closes the login screen
    }

    
    std::unique_ptr<MarketplaceScreen> marketplaceScreen = std::make_unique<MarketplaceScreen>(username,"F:\\sem3\\OOP\\oop-project\\assets\\Marketplace.txt");
    

    NavBar navBar(font);
    Screen currentScreen = MARKETPLACE; // Default to Marketplace screen
    bool isLoggedOut = false;



    std::unique_ptr<MarketplaceScreen> eventScreen = std::make_unique<EventScreen>(username);

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

                // Reinitialize screens for the new user
                marketplaceScreen = std::make_unique<MarketplaceScreen>(username,"F:\\sem3\\OOP\\oop-project\\assets\\Marketplace.txt");
                eventScreen = std::make_unique<EventScreen>(username);
                navBar = NavBar(font); // Reinitialize NavBar to avoid stale state
                currentScreen = MARKETPLACE; // Reset to default screen
                isLoggedOut = false; // Reset logout flag
            }

            // Handle events for the current screen
            switch (currentScreen) {
                case MARKETPLACE:
                    marketplaceScreen->handleEvents(window, event);
                    break;

                case GOSSIP: {
                    // Handle Gossip screen events
                    sf::RenderWindow gossipWindow(sf::VideoMode(800, 600), "Post Feed");
                    PostFeed gossipFeed(&gossipWindow); // Initialize the PostFeed object for the Gossip window

                    while (gossipWindow.isOpen()) {
                        sf::Event gossipEvent;
                        while (gossipWindow.pollEvent(gossipEvent)) {
                            if (gossipEvent.type == sf::Event::Closed) {
                                gossipWindow.close(); // Close the Gossip window
                            }
                            gossipFeed.handleEvent(gossipEvent, username); // Pass the username dynamically
                        }

                        gossipWindow.clear(sf::Color::White);
                        gossipFeed.draw(); // Render the posts in the Gossip feed
                        gossipWindow.display();
                    }

                    // After Gossip window is closed, switch back to the default screen
                    currentScreen = MARKETPLACE;
                }
                break;

                case EVENTS:
                    if (eventScreen) {
                        eventScreen->handleEvents(window, event);
                    }
                    break;

                case PROFILE:
                    AuthScreen::showProfileScreen(window, username, batch, major);
                    currentScreen = MARKETPLACE;
                    break;
            }
        }

        // Render the current screen
        window.clear(sf::Color::White);
        switch (currentScreen) {
            case MARKETPLACE:
                marketplaceScreen->render(window);
                break;

            case EVENTS:
                if (eventScreen) {
                    eventScreen->render(window);
                }
                break;

            case PROFILE:
                AuthScreen::showProfileScreen(window, username, batch, major);
                marketplaceScreen->render(window);
                break;
            
        }

        // Render navigation bar on top
        navBar.render(window);
        window.display();
    }

    return 0;
}
