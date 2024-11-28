#include "LoginScreen.hpp"
#include "Button.hpp"
#include "TextInput.hpp"
#include "FileHandler.hpp"
#include "HomeScreen.hpp"
#include <iostream>
#include "Gossip/gossip.cpp"

bool LoginScreen::show(sf::RenderWindow& window, std::string& loggedInUser) {
    sf::Font font;
    if (!font.loadFromFile("Marketplace/Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return false;
    }

    sf::Text title("Login", font, 30);
    title.setPosition(300, 50);

    TextInput usernameInput({250, 150}, {200, 30}, font, "Enter username");
    TextInput passwordInput({250, 200}, {200, 30}, font, "Enter password");

    Button loginButton({250, 300}, {100, 40}, "Login", font, sf::Color::Blue, sf::Color::White);
    Button signupButton({370, 300}, {100, 40}, "Signup", font, sf::Color::Green, sf::Color::White);

    sf::Text errorText("", font, 15);
    errorText.setPosition(150, 400);
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

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (loginButton.isClicked(mousePos)) {
                    std::string username = usernameInput.getText();
                    std::string password = passwordInput.getText();

                    if (username.empty() || password.empty()) {
                        errorText.setString("Please fill in both fields.");
                    } else {
                        auto users = FileHandler::loadUsers("users.txt");
                        bool validUser = false;

                        for (const auto& user : users) {
                            if (user.username == username && user.password == password) {
                                validUser = true;
                                loggedInUser = username;
                                break;
                            }
                        }

                        if (validUser) {
                            sf::RenderWindow window(sf::VideoMode(800, 600), "Post Feed");
    PostFeed feed(&window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            feed.handleEvent(event);
        }

        window.clear(sf::Color::White);
        feed.draw();
        window.display();
    }
                        } else {
                            errorText.setString("Invalid username or password.");
                        }
                    }
                }

                if (signupButton.isClicked(mousePos)) {
                    return false;  // Switch to SignupScreen
                }
            }
        }

        window.clear();
        window.draw(title);
        usernameInput.draw(window);
        passwordInput.draw(window);
        loginButton.draw(window);
        signupButton.draw(window);
        window.draw(errorText);
        window.display();
    }

    return false;
}
