#include "../include/FormWindow.h"
#include "../include/FileDialog.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> // For multiple images

bool openFormWindow(std::string& name, std::string& description, int& price, std::vector<std::string>& imagePaths) {
    sf::RenderWindow formWindow(sf::VideoMode(400, 450), "Add Item");
    sf::Font font;

    // Load the font
    if (!font.loadFromFile("F:\\sem3\\OOP\\oop-project\\assets\\Arial.ttf")) {
        std::cerr << "Error: Could not load font from path!" << std::endl;
        return false;
    }

    // Title
    sf::Text title("Add New Item", font, 20);
    title.setPosition(120, 10);
    title.setFillColor(sf::Color::Black);

    // Labels
    sf::Text nameLabel("Name:", font, 15);
    nameLabel.setPosition(20, 60);
    nameLabel.setFillColor(sf::Color::Black);

    sf::Text descriptionLabel("Description:", font, 15);
    descriptionLabel.setPosition(20, 110);
    descriptionLabel.setFillColor(sf::Color::Black);

    sf::Text priceLabel("Price:", font, 15);
    priceLabel.setPosition(20, 160);
    priceLabel.setFillColor(sf::Color::Black);

    sf::Text imageLabel("Images:", font, 15);
    imageLabel.setPosition(20, 210);
    imageLabel.setFillColor(sf::Color::Black);

    // Input field backgrounds
    sf::RectangleShape nameField(sf::Vector2f(250, 25));
    nameField.setPosition(120, 60);
    nameField.setFillColor(sf::Color(230, 230, 230)); // Light gray

    sf::RectangleShape descriptionField(sf::Vector2f(250, 25));
    descriptionField.setPosition(120, 110);
    descriptionField.setFillColor(sf::Color(230, 230, 230));

    sf::RectangleShape priceField(sf::Vector2f(250, 25));
    priceField.setPosition(120, 160);
    priceField.setFillColor(sf::Color(230, 230, 230));

    // Image button
    sf::RectangleShape imageButton(sf::Vector2f(150, 30));
    imageButton.setPosition(120, 210);
    imageButton.setFillColor(sf::Color::Blue);

    sf::Text imageButtonText("Add Image", font, 15);
    imageButtonText.setPosition(135, 215);
    imageButtonText.setFillColor(sf::Color::White);

    sf::Text imageCountText("Images Added: 0", font, 12);
    imageCountText.setPosition(20, 260);
    imageCountText.setFillColor(sf::Color::Black);

    // Input field texts
    sf::String inputName, inputDescription, inputPrice;
    sf::Text nameText("", font, 15);
    nameText.setPosition(125, 63);
    nameText.setFillColor(sf::Color::Black);

    sf::Text descriptionText("", font, 15);
    descriptionText.setPosition(125, 113);
    descriptionText.setFillColor(sf::Color::Black);

    sf::Text priceText("", font, 15);
    priceText.setPosition(125, 163);
    priceText.setFillColor(sf::Color::Black);

    // Submit button
    sf::RectangleShape submitButton(sf::Vector2f(100, 30));
    submitButton.setFillColor(sf::Color::Green);
    submitButton.setPosition(150, 350);

    sf::Text submitText("Submit", font, 15);
    submitText.setPosition(170, 355);
    submitText.setFillColor(sf::Color::White);

    // Active field tracking
    enum ActiveField { NAME, DESCRIPTION, PRICE, NONE };
    ActiveField activeField = NAME;

    auto setActiveField = [&](ActiveField field) {
        activeField = field;

        nameField.setFillColor(sf::Color(230, 230, 230));
        descriptionField.setFillColor(sf::Color(230, 230, 230));
        priceField.setFillColor(sf::Color(230, 230, 230));

        if (activeField == NAME) nameField.setFillColor(sf::Color::White);
        else if (activeField == DESCRIPTION) descriptionField.setFillColor(sf::Color::White);
        else if (activeField == PRICE) priceField.setFillColor(sf::Color::White);
    };

    setActiveField(NAME);

    while (formWindow.isOpen()) {
        sf::Event event;
        while (formWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                formWindow.close();
                return false;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (activeField == NAME && !inputName.isEmpty()) inputName.erase(inputName.getSize() - 1, 1);
                    else if (activeField == DESCRIPTION && !inputDescription.isEmpty()) inputDescription.erase(inputDescription.getSize() - 1, 1);
                    else if (activeField == PRICE && !inputPrice.isEmpty()) inputPrice.erase(inputPrice.getSize() - 1, 1);
                } else if (event.text.unicode < 128 && event.text.unicode >= 32) {
                    if (activeField == NAME) inputName += static_cast<char>(event.text.unicode);
                    else if (activeField == DESCRIPTION) inputDescription += static_cast<char>(event.text.unicode);
                    else if (activeField == PRICE && isdigit(event.text.unicode)) inputPrice += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(formWindow);

                if (nameField.getGlobalBounds().contains(mousePos.x, mousePos.y)) setActiveField(NAME);
                else if (descriptionField.getGlobalBounds().contains(mousePos.x, mousePos.y)) setActiveField(DESCRIPTION);
                else if (priceField.getGlobalBounds().contains(mousePos.x, mousePos.y)) setActiveField(PRICE);
                else if (imageButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::string selectedImage = openFileDialog();
                    if (!selectedImage.empty()) {
                        imagePaths.push_back(selectedImage);
                        imageCountText.setString("Images Added: " + std::to_string(imagePaths.size()));
                    }
                } else if (submitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (!inputName.isEmpty() && !inputDescription.isEmpty() && !inputPrice.isEmpty() && !imagePaths.empty()) {
                        try {
                            price = std::stoi(inputPrice.toAnsiString());
                            name = inputName.toAnsiString();
                            description = inputDescription.toAnsiString();
                            formWindow.close();
                            return true;
                        } catch (...) {
                            std::cerr << "Invalid price input!" << std::endl;
                        }
                    } else {
                        std::cerr << "Please fill all fields and add at least one image!" << std::endl;
                    }
                }
            }
        }

        nameText.setString(inputName);
        descriptionText.setString(inputDescription);
        priceText.setString(inputPrice);

        formWindow.clear(sf::Color::White);

        formWindow.draw(title);
        formWindow.draw(nameLabel);
        formWindow.draw(descriptionLabel);
        formWindow.draw(priceLabel);
        formWindow.draw(imageLabel);

        formWindow.draw(nameField);
        formWindow.draw(descriptionField);
        formWindow.draw(priceField);

        formWindow.draw(nameText);
        formWindow.draw(descriptionText);
        formWindow.draw(priceText);

        formWindow.draw(imageButton);
        formWindow.draw(imageButtonText);
        formWindow.draw(imageCountText);

        formWindow.draw(submitButton);
        formWindow.draw(submitText);

        formWindow.display();
    }

    return false;
}
bool openEFormWindow(std::string& name, std::string& description, int& price, std::vector<std::string>& imagePaths) {
    sf::RenderWindow formWindow(sf::VideoMode(400, 450), "Add Event");
    sf::Font font;

    // Load the font
    if (!font.loadFromFile("F:\\sem3\\OOP\\oop-project\\assets\\Arial.ttf")) {
        std::cerr << "Error: Could not load font from path!" << std::endl;
        return false;
    }

    // Title
    sf::Text title("Add New Event", font, 20);
    title.setPosition(120, 10);
    title.setFillColor(sf::Color::Black);

    // Labels
    sf::Text nameLabel("Name:", font, 15);
    nameLabel.setPosition(20, 60);
    nameLabel.setFillColor(sf::Color::Black);

    sf::Text descriptionLabel("Venue:", font, 15);
    descriptionLabel.setPosition(20, 110);
    descriptionLabel.setFillColor(sf::Color::Black);

    sf::Text priceLabel("Ticket Price:", font, 15);
    priceLabel.setPosition(20, 160);
    priceLabel.setFillColor(sf::Color::Black);

    sf::Text imageLabel("Images:", font, 15);
    imageLabel.setPosition(20, 210);
    imageLabel.setFillColor(sf::Color::Black);

    // Input field backgrounds
    sf::RectangleShape nameField(sf::Vector2f(250, 25));
    nameField.setPosition(120, 60);
    nameField.setFillColor(sf::Color(230, 230, 230)); // Light gray

    sf::RectangleShape descriptionField(sf::Vector2f(250, 25));
    descriptionField.setPosition(120, 110);
    descriptionField.setFillColor(sf::Color(230, 230, 230));

    sf::RectangleShape priceField(sf::Vector2f(250, 25));
    priceField.setPosition(120, 160);
    priceField.setFillColor(sf::Color(230, 230, 230));

    // Image button
    sf::RectangleShape imageButton(sf::Vector2f(150, 30));
    imageButton.setPosition(120, 210);
    imageButton.setFillColor(sf::Color::Blue);

    sf::Text imageButtonText("Add Image", font, 15);
    imageButtonText.setPosition(135, 215);
    imageButtonText.setFillColor(sf::Color::White);

    sf::Text imageCountText("Images Added: 0", font, 12);
    imageCountText.setPosition(20, 260);
    imageCountText.setFillColor(sf::Color::Black);

    // Input field texts
    sf::String inputName, inputDescription, inputPrice;
    sf::Text nameText("", font, 15);
    nameText.setPosition(125, 63);
    nameText.setFillColor(sf::Color::Black);

    sf::Text descriptionText("", font, 15);
    descriptionText.setPosition(125, 113);
    descriptionText.setFillColor(sf::Color::Black);

    sf::Text priceText("", font, 15);
    priceText.setPosition(125, 163);
    priceText.setFillColor(sf::Color::Black);

    // Submit button
    sf::RectangleShape submitButton(sf::Vector2f(100, 30));
    submitButton.setFillColor(sf::Color::Green);
    submitButton.setPosition(150, 350);

    sf::Text submitText("Submit", font, 15);
    submitText.setPosition(170, 355);
    submitText.setFillColor(sf::Color::White);

    // Active field tracking
    enum ActiveField { NAME, DESCRIPTION, PRICE, NONE };
    ActiveField activeField = NAME;

    auto setActiveField = [&](ActiveField field) {
        activeField = field;

        nameField.setFillColor(sf::Color(230, 230, 230));
        descriptionField.setFillColor(sf::Color(230, 230, 230));
        priceField.setFillColor(sf::Color(230, 230, 230));

        if (activeField == NAME) nameField.setFillColor(sf::Color::White);
        else if (activeField == DESCRIPTION) descriptionField.setFillColor(sf::Color::White);
        else if (activeField == PRICE) priceField.setFillColor(sf::Color::White);
    };

    setActiveField(NAME);

    while (formWindow.isOpen()) {
        sf::Event event;
        while (formWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                formWindow.close();
                return false;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (activeField == NAME && !inputName.isEmpty()) inputName.erase(inputName.getSize() - 1, 1);
                    else if (activeField == DESCRIPTION && !inputDescription.isEmpty()) inputDescription.erase(inputDescription.getSize() - 1, 1);
                    else if (activeField == PRICE && !inputPrice.isEmpty()) inputPrice.erase(inputPrice.getSize() - 1, 1);
                } else if (event.text.unicode < 128 && event.text.unicode >= 32) {
                    if (activeField == NAME) inputName += static_cast<char>(event.text.unicode);
                    else if (activeField == DESCRIPTION) inputDescription += static_cast<char>(event.text.unicode);
                    else if (activeField == PRICE && isdigit(event.text.unicode)) inputPrice += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(formWindow);

                if (nameField.getGlobalBounds().contains(mousePos.x, mousePos.y)) setActiveField(NAME);
                else if (descriptionField.getGlobalBounds().contains(mousePos.x, mousePos.y)) setActiveField(DESCRIPTION);
                else if (priceField.getGlobalBounds().contains(mousePos.x, mousePos.y)) setActiveField(PRICE);
                else if (imageButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::string selectedImage = openFileDialog();
                    if (!selectedImage.empty()) {
                        imagePaths.push_back(selectedImage);
                        imageCountText.setString("Images Added: " + std::to_string(imagePaths.size()));
                    }
                } else if (submitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (!inputName.isEmpty() && !inputDescription.isEmpty() && !inputPrice.isEmpty() && !imagePaths.empty()) {
                        try {
                            price = std::stoi(inputPrice.toAnsiString());
                            name = inputName.toAnsiString();
                            description = inputDescription.toAnsiString();
                            formWindow.close();
                            return true;
                        } catch (...) {
                            std::cerr << "Invalid price input!" << std::endl;
                        }
                    } else {
                        std::cerr << "Please fill all fields and add at least one image!" << std::endl;
                    }
                }
            }
        }

        nameText.setString(inputName);
        descriptionText.setString(inputDescription);
        priceText.setString(inputPrice);

        formWindow.clear(sf::Color::White);

        formWindow.draw(title);
        formWindow.draw(nameLabel);
        formWindow.draw(descriptionLabel);
        formWindow.draw(priceLabel);
        formWindow.draw(imageLabel);

        formWindow.draw(nameField);
        formWindow.draw(descriptionField);
        formWindow.draw(priceField);

        formWindow.draw(nameText);
        formWindow.draw(descriptionText);
        formWindow.draw(priceText);

        formWindow.draw(imageButton);
        formWindow.draw(imageButtonText);
        formWindow.draw(imageCountText);

        formWindow.draw(submitButton);
        formWindow.draw(submitText);

        formWindow.display();
    }

    return false;
}
