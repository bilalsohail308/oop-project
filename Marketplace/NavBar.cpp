#include "NavBar.h"
#include <iostream>

NavBar::NavBar(const sf::Font& font) : font(font), activeButton(-1) {
    // Set up the navigation bar background
    background.setSize(sf::Vector2f(800, BUTTON_HEIGHT));
    background.setFillColor(sf::Color(50, 50, 50));

    // Define button labels
    std::vector<std::string> labels = {"Gossip", "Marketplace", "Events", "Ticketing"};

    float buttonWidth = 120.0f;
    float buttonHeight = 30.0f;
    float padding = 10.0f; // Spacing between buttons

    // Calculate spacing dynamically
    float startX = padding;
    float spacePerButton = (800 - (2 * buttonWidth) - (labels.size() - 1) * padding) / labels.size();

    // Initialize buttons
    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text button(labels[i], font, 18);
        button.setFillColor(sf::Color::White);
        button.setPosition(startX + i * (spacePerButton + padding), 10);
        buttons.push_back(button);
    }

    // Initialize the "Logout" button
    logoutButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    logoutButton.setPosition(800 - (2 * buttonWidth + padding), padding); // Position near the top-right corner
    logoutButton.setFillColor(sf::Color::Red);

    logoutButtonText.setFont(font);
    logoutButtonText.setString("Logout");
    logoutButtonText.setCharacterSize(15);
    logoutButtonText.setFillColor(sf::Color::White);
    logoutButtonText.setPosition(
        logoutButton.getPosition().x + (buttonWidth - logoutButtonText.getLocalBounds().width) / 2,
        logoutButton.getPosition().y + (buttonHeight - logoutButtonText.getLocalBounds().height) / 2 - 5);

    // Initialize the "My Profile" button
    profileButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    profileButton.setPosition(800 - buttonWidth - padding, padding); // Position at top-right corner
    profileButton.setFillColor(sf::Color::Blue);

    profileButtonText.setFont(font);
    profileButtonText.setString("My Profile");
    profileButtonText.setCharacterSize(15);
    profileButtonText.setFillColor(sf::Color::White);
    profileButtonText.setPosition(
        profileButton.getPosition().x + (buttonWidth - profileButtonText.getLocalBounds().width) / 2,
        profileButton.getPosition().y + (buttonHeight - profileButtonText.getLocalBounds().height) / 2 - 5);
}


// Handle events
void NavBar::handleEvents(sf::RenderWindow& window, sf::Event& event, Screen& currentScreen, bool& isLoggedOut) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Check navigation buttons
        for (size_t i = 0; i < buttons.size(); ++i) {
            sf::FloatRect buttonBounds = buttons[i].getGlobalBounds();
            if (buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                activeButton = i; // Update the active button index
                currentScreen = static_cast<Screen>(i); // Update the current screen
                return; // Exit after handling the click
            }
        }

        // Check if the "My Profile" button is clicked
        if (profileButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            currentScreen = PROFILE; // Switch to the PROFILE screen
            return;
        }

        // Check if the "Logout" button is clicked
        if (logoutButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        isLoggedOut = true; // Signal the main loop to log out
         return; 
        }
    }
}


// Render the navigation bar
void NavBar::render(sf::RenderWindow& window) {
    // Draw the background
    window.draw(background);

    // Draw navigation buttons
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (static_cast<int>(i) == activeButton) {
            buttons[i].setFillColor(sf::Color::Yellow); // Highlight the active button
        } else {
            buttons[i].setFillColor(sf::Color::White);
        }
        window.draw(buttons[i]);
    }

    // Draw the "My Profile" button
    window.draw(profileButton);
    window.draw(profileButtonText);

    // Draw the "Logout" button
    window.draw(logoutButton);
    window.draw(logoutButtonText);
}
