#include "ManageEvents.h"
#include <iostream>

void handleEvents(sf::RenderWindow& window, std::vector<Event>& events) {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return;
    }

    // UI Elements
    sf::RectangleShape addEventButton(sf::Vector2f(150, 40));
    addEventButton.setFillColor(sf::Color::Green);
    addEventButton.setPosition(325, 10);

    sf::Text addEventText("Add Event", font, 20);
    addEventText.setPosition(355, 15);
    addEventText.setFillColor(sf::Color::White);

    sf::RectangleShape backToHomeButton(sf::Vector2f(150, 40));
    backToHomeButton.setFillColor(sf::Color::Red);
    backToHomeButton.setPosition(10, 10);

    sf::Text backToHomeText("Back", font, 15);
    backToHomeText.setPosition(15, 15);
    backToHomeText.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Check if "Add Event" button is clicked
                if (addEventButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::string name, description, date, venue, imagePath;
                    if (openEventFormWindow(name, description, date, venue, imagePath)) {
                        events.emplace_back(name, description, date, venue, imagePath);
                    }
                }

                // Check if "Back" button is clicked
                if (backToHomeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; // Close Events and return to Home Screen
                }
            }
        }

        window.clear(sf::Color::White);
        renderUI(window, events, font);
        window.display();
    }
}

void renderUI(sf::RenderWindow& window, std::vector<Event>& events, sf::Font& font) {
    // Draw UI components (Title, Buttons, etc.)
    sf::Text title("Events", font, 30);
    title.setPosition(350, 10);
    title.setFillColor(sf::Color::Black);
    window.draw(title);

    // Draw buttons
    sf::RectangleShape addEventButton(sf::Vector2f(150, 40));
    addEventButton.setFillColor(sf::Color::Green);
    addEventButton.setPosition(325, 10);

    sf::Text addEventText("Add Event", font, 20);
    addEventText.setPosition(355, 15);
    addEventText.setFillColor(sf::Color::White);
    window.draw(addEventButton);
    window.draw(addEventText);

    sf::RectangleShape backToHomeButton(sf::Vector2f(150, 40));
    backToHomeButton.setFillColor(sf::Color::Red);
    backToHomeButton.setPosition(10, 10);

    sf::Text backToHomeText("Back", font, 15);
    backToHomeText.setPosition(15, 15);
    backToHomeText.setFillColor(sf::Color::White);
    window.draw(backToHomeButton);
    window.draw(backToHomeText);

    // Render events
    const int PADDING = 20;
    int nextX = 20, nextY = 120;
    for (const auto& event : events) {
        event.render(window, nextX, nextY, font);
        nextX += Event::BOX_WIDTH + PADDING;

        if (nextX + Event::BOX_WIDTH > window.getSize().x) {
            nextX = 20;
            nextY += Event::BOX_HEIGHT + PADDING;
        }
    }
}

bool openEventFormWindow(std::string& name, std::string& description, std::string& date, std::string& venue, std::string& imagePath) {
    // Implement the event form window (e.g., using input fields for the event details)
    // For simplicity, returning true for now
    return true;
}
