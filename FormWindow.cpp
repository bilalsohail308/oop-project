// FormWindow.cpp
#include "FormWindow.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cctype>
#include "FileDialog.h" // Make sure this header is available and properly linked

bool openFormWindow(std::string& name, std::string& description, int& price, std::string& imagePath) {
    sf::RenderWindow formWindow(sf::VideoMode(400, 350), "Add Item");
    sf::Font font;

    // Load the font
    if (!font.loadFromFile("C:/Users/LENOVO/OneDrive/Desktop/Cpp/project.cpp/Arial.ttf")) {
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

    sf::Text imageLabel("Image:", font, 15);
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
    sf::RectangleShape imageButton(sf::Vector2f(120, 30));
    imageButton.setPosition(120, 210);
    imageButton.setFillColor(sf::Color::Blue);

    sf::Text imageButtonText("Choose Image", font, 15);
    imageButtonText.setPosition(125, 215);
    imageButtonText.setFillColor(sf::Color::White);

    sf::Text imagePathText("", font, 12);
    imagePathText.setPosition(20, 250);
    imagePathText.setFillColor(sf::Color::Black);

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
    submitButton.setFillColor(sf::Color::Blue);
    submitButton.setPosition(150, 290);

    sf::Text submitText("Submit", font, 15);
    submitText.setPosition(170, 295);
    submitText.setFillColor(sf::Color::White);

    // Active field tracking
    enum ActiveField { NAME, DESCRIPTION, PRICE, NONE };
    ActiveField activeField = NAME;

    // Function to set the active field and provide visual feedback
    auto setActiveField = [&](ActiveField field) {
        activeField = field;

        // Reset all fields to default color
        nameField.setFillColor(sf::Color(230, 230, 230));
        descriptionField.setFillColor(sf::Color(230, 230, 230));
        priceField.setFillColor(sf::Color(230, 230, 230));

        // Highlight the active field
        if (activeField == NAME) {
            nameField.setFillColor(sf::Color::White); // Highlighted color
        } else if (activeField == DESCRIPTION) {
            descriptionField.setFillColor(sf::Color::White);
        } else if (activeField == PRICE) {
            priceField.setFillColor(sf::Color::White);
        }
    };

    setActiveField(NAME); // Start with the name field active

    // Render loop
    while (formWindow.isOpen()) {
        sf::Event event;
        while (formWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                formWindow.close();
                return false; // User closed the form
            }

            // Handle text input
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Handle backspace
                    if (activeField == NAME && !inputName.isEmpty())
                        inputName.erase(inputName.getSize() - 1, 1);
                    else if (activeField == DESCRIPTION && !inputDescription.isEmpty())
                        inputDescription.erase(inputDescription.getSize() - 1, 1);
                    else if (activeField == PRICE && !inputPrice.isEmpty())
                        inputPrice.erase(inputPrice.getSize() - 1, 1);
                } else if (event.text.unicode < 128 && event.text.unicode >= 32) { // Handle regular input
                    if (activeField == NAME)
                        inputName += static_cast<char>(event.text.unicode);
                    else if (activeField == DESCRIPTION)
                        inputDescription += static_cast<char>(event.text.unicode);
                    else if (activeField == PRICE && isdigit(event.text.unicode)) // Only allow digits in price
                        inputPrice += static_cast<char>(event.text.unicode);
                }
            }

            // Handle field navigation with Tab or Enter
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Tab || event.key.code == sf::Keyboard::Enter) {
                    if (activeField == NAME)
                        setActiveField(DESCRIPTION);
                    else if (activeField == DESCRIPTION)
                        setActiveField(PRICE);
                    else if (activeField == PRICE)
                        setActiveField(NAME);
                }
            }

            // Handle mouse clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(formWindow);

                if (nameField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    setActiveField(NAME);
                } else if (descriptionField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    setActiveField(DESCRIPTION);
                } else if (priceField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    setActiveField(PRICE);
                } else if (imageButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Open file dialog for image selection
                    std::string selectedImage = openFileDialog();
                    if (!selectedImage.empty()) {
                        imagePath = selectedImage;
                        imagePathText.setString("Image: " + selectedImage);
                    }
                } else if (submitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Handle submission
                    if (!inputName.isEmpty() && !inputDescription.isEmpty() && !inputPrice.isEmpty() && !imagePath.empty()) {
                        try {
                            price = std::stoi(inputPrice.toAnsiString());
                            name = inputName.toAnsiString();
                            description = inputDescription.toAnsiString();
                            formWindow.close();
                            return true; // Successfully submitted
                        } catch (...) {
                            std::cerr << "Invalid price input!" << std::endl;
                        }
                    } else {
                        std::cerr << "Please fill all fields and choose an image!" << std::endl;
                    }
                }
            }
        }

        // Update text fields
        nameText.setString(inputName);
        descriptionText.setString(inputDescription);
        priceText.setString(inputPrice);

        // Render form
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
        formWindow.draw(imagePathText);

        formWindow.draw(submitButton);
        formWindow.draw(submitText);

        formWindow.display();
    }

    return false;
}
