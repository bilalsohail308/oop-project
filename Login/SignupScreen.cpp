#include "SignupScreen.hpp"
#include "TextInput.hpp"
#include "Button.hpp"
#include "FileHandler.hpp"
#include "LoginScreen.hpp"
#include <iostream>

bool SignupScreen::show(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Marketplace/Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return false;
    }

    sf::Text title("Signup", font, 30);
    title.setPosition(300, 50);

    TextInput usernameInput({250, 150}, {200, 30}, font, "Enter username");
    TextInput passwordInput({250, 200}, {200, 30}, font, "Enter password");
    TextInput batchInput({250, 250}, {200, 30}, font, "Enter batch");
    TextInput majorInput({250, 300}, {200, 30}, font, "Enter major");

    Button signupButton({250, 400}, {100, 40}, "Signup", font, sf::Color::Green, sf::Color::White);
    Button backButton({370, 400}, {100, 40}, "Back", font, sf::Color::Red, sf::Color::White);

    sf::Text errorText("", font, 15);
    errorText.setPosition(150, 450);
    errorText.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }

            usernameInput.handleEvent(event);
            passwordInput.handleEvent(event);
            batchInput.handleEvent(event);
            majorInput.handleEvent(event);

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (signupButton.isClicked(mousePos)) {
                    std::string username = usernameInput.getText();
                    std::string password = passwordInput.getText();
                    std::string batch = batchInput.getText();
                    std::string major = majorInput.getText();

                    if (username.empty() || password.empty() || batch.empty() || major.empty()) {
                        errorText.setString("All fields are required.");
                    } else if (FileHandler::userExists("users.txt", username)) {
                        errorText.setString("Username already exists.");
                    } else {
                        User newUser(username, password, batch, major);
                        auto users = FileHandler::loadUsers("users.txt");
                        users.push_back(newUser);
                        FileHandler::saveUsers("users.txt", users);
                        return true;  // Return to LoginScreen
                    }
                }

                if (backButton.isClicked(mousePos)) {
                    return false;  // Return to LoginScreen
                }
            }
        }

        window.clear();
        window.draw(title);
        usernameInput.draw(window);
        passwordInput.draw(window);
        batchInput.draw(window);
        majorInput.draw(window);
        signupButton.draw(window);
        backButton.draw(window);
        window.draw(errorText);
        window.display();
    }

    return false;
}
