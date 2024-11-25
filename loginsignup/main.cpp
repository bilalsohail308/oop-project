#include "AuthScreen.h"
#include "Event.h"
#include "FormWindow.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void manageEvents(sf::RenderWindow& window, std::vector<Event>& events) {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return;
    }

    sf::Text title("Events", font, 30);
    title.setPosition(350, 10);
    title.setFillColor(sf::Color::Black);

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

    const int PADDING = 20;
    int nextX = 20, nextY = 120;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (addEventButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::string name, description, date, venue, imagePath;
                    if (openEventFormWindow(name, description, date, venue, imagePath)) {
                        events.emplace_back(name, description, date, venue, imagePath);
                    }
                }

                if (backToHomeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; // Close Events and return to Home Screen
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw UI components
        window.draw(title);
        window.draw(addEventButton);
        window.draw(addEventText);
        window.draw(backToHomeButton);
        window.draw(backToHomeText);

        
        nextX = 20;
        nextY = 120;
        for (const auto& event : events) {
            sf::RectangleShape eventBox = event.box;
            eventBox.setPosition(nextX, nextY);

            sf::Text nameText(event.name, font, 15);
            nameText.setPosition(nextX + 10, nextY + 10);
            nameText.setFillColor(sf::Color::Black);

            sf::Text dateText("Date: " + event.date, font, 12);
            dateText.setPosition(nextX + 10, nextY + 40);
            dateText.setFillColor(sf::Color::Black);

            sf::Text venueText("Venue: " + event.venue, font, 12);
            venueText.setPosition(nextX + 10, nextY + 60);
            venueText.setFillColor(sf::Color::Black);

            window.draw(eventBox);
            window.draw(nameText);
            window.draw(dateText);
            window.draw(venueText);

            nextX += Event::BOX_WIDTH + PADDING;
            if (nextX + Event::BOX_WIDTH > window.getSize().x) {
                nextX = 20;
                nextY += Event::BOX_HEIGHT + PADDING;
            }
        }

        window.display();
    }
}

int main() {
    const std::string usersFilePath = "users.txt";
    sf::RenderWindow window(sf::VideoMode(800, 600), "HU Bazaar");

    std::string username, batch, major;

    while (window.isOpen()) {
        if (AuthScreen::loginScreen(window, usersFilePath, username, batch, major)) {
            sf::RenderWindow homeWindow(sf::VideoMode(800, 600), "Home Screen");
            std::vector<Event> events;

            sf::Font font;
            if (!font.loadFromFile("Arial.ttf")) {
                std::cerr << "Error loading font!" << std::endl;
                return -1;
            }

            sf::RectangleShape profileButton(sf::Vector2f(100, 30));
            profileButton.setPosition(10, 10);
            profileButton.setFillColor(sf::Color(128, 0, 128));

            sf::RectangleShape logoutButton(sf::Vector2f(100, 30));
            logoutButton.setPosition(680, 10);
            logoutButton.setFillColor(sf::Color::Red);

            sf::RectangleShape eventsButton(sf::Vector2f(100, 30));
            eventsButton.setPosition(340, 10);
            eventsButton.setFillColor(sf::Color::Green);

            sf::Text profileButtonText("Profile", font, 15);
            profileButtonText.setPosition(25, 15);

            sf::Text logoutButtonText("Logout", font, 15);
            logoutButtonText.setPosition(695, 15);

            sf::Text eventsButtonText("Events", font, 15);
            eventsButtonText.setPosition(355, 15);

            while (homeWindow.isOpen()) {
                sf::Event event;
                while (homeWindow.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        homeWindow.close();

                    if (event.type == sf::Event::MouseButtonPressed) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(homeWindow);

                        if (profileButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            AuthScreen::showProfileScreen(homeWindow, username, batch, major);
                        } else if (logoutButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            homeWindow.close();
                            window.create(sf::VideoMode(800, 600), "HU Bazaar");
                        } else if (eventsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            manageEvents(homeWindow, events);
                        }
                    }
                }

                homeWindow.clear(sf::Color::White);
                homeWindow.draw(profileButton);
                homeWindow.draw(logoutButton);
                homeWindow.draw(eventsButton);
                homeWindow.draw(profileButtonText);
                homeWindow.draw(logoutButtonText);
                homeWindow.draw(eventsButtonText);
                homeWindow.display();
            }
        } else {
            break;
        }
    }

    return 0;
}
