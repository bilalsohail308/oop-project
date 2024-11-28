#include "ProfileScreen.hpp"
#include "Button.hpp"
#include "TextInput.hpp"
#include "FileHandler.hpp"
#include "Marketplace/FileDialog.h" // For image selection
#include <iostream>

void ProfileScreen::show(sf::RenderWindow& window, const std::string& username) {
    sf::Font font;
    if (!font.loadFromFile("Marketplace/Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    sf::Text title("Profile", font, 30);
    title.setPosition(300, 50);

    auto users = FileHandler::loadUsers("users.txt");
    User* currentUser = nullptr;

    for (auto& user : users) {
        if (user.username == username) {
            currentUser = &user;
            break;
        }
    }

    if (!currentUser) {
        std::cerr << "User not found!" << std::endl;
        return;
    }

    TextInput batchInput({250, 150}, {200, 30}, font, currentUser->batch);
    TextInput majorInput({250, 200}, {200, 30}, font, currentUser->major);

    sf::Text profilePicLabel("Profile Picture:", font, 15);
    profilePicLabel.setPosition(150, 250);

    Button uploadPicButton({250, 250}, {150, 40}, "Upload", font, sf::Color::Blue, sf::Color::White);
    Button saveButton({250, 350}, {100, 40}, "Save", font, sf::Color::Green, sf::Color::White);
    Button backButton({370, 350}, {100, 40}, "Back", font, sf::Color::Red, sf::Color::White);

    sf::Text successText("", font, 15);
    successText.setPosition(150, 400);
    successText.setFillColor(sf::Color::Green);

    std::string profilePicturePath = currentUser->profilePicture;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            batchInput.handleEvent(event);
            majorInput.handleEvent(event);

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (uploadPicButton.isClicked(mousePos)) {
                    std::string selectedImage = openFileDialog();
                    if (!selectedImage.empty()) {
                        profilePicturePath = selectedImage;
                    }
                }

                if (saveButton.isClicked(mousePos)) {
                    currentUser->batch = batchInput.getText();
                    currentUser->major = majorInput.getText();
                    currentUser->profilePicture = profilePicturePath;

                    FileHandler::saveUsers("users.txt", users);
                    successText.setString("Profile updated successfully!");
                }

                if (backButton.isClicked(mousePos)) {
                    return;  // Go back to HomeScreen
                }
            }
        }

        window.clear();
        window.draw(title);
        batchInput.draw(window);
        majorInput.draw(window);
        uploadPicButton.draw(window);
        saveButton.draw(window);
        backButton.draw(window);
        window.draw(successText);

        // Display profile picture
        if (!profilePicturePath.empty()) {
            sf::Texture profilePicTexture;
            if (profilePicTexture.loadFromFile(profilePicturePath)) {
                sf::Sprite profilePicSprite(profilePicTexture);
                profilePicSprite.setPosition(500, 150);
                profilePicSprite.setScale(0.2f, 0.2f);  // Adjust scaling
                window.draw(profilePicSprite);
            }
        }

        window.display();
    }
}
