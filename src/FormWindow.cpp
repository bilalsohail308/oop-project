#include "../include/FormWindow.h"
#include "../include/FileDialog.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> // For multiple images

bool openFormWindow(std::string& name, std::string& description, int& price, std::vector<std::string>& imagePaths) {
    sf::RenderWindow formWindow(sf::VideoMode(400, 450), "Add Item");
    sf::Font font;

    // Load the font
    if (!font.loadFromFile("../assets/Arial.ttf")) {
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
    if (!font.loadFromFile("../assets/Arial.ttf")) {
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
bool openTicketingForm(std::string& name, std::string& contactNumber, std::string& paymentID) {
    sf::RenderWindow formWindow(sf::VideoMode(400, 350), "Ticketing Form");
    sf::Font font;

    // Load the font
    if (!font.loadFromFile("assets\\Arial.ttf")) {
        std::cerr << "Error: Could not load font from path!" << std::endl;
        return false;
    }

    // Title
    sf::Text title("Ticketing", font, 20);
    title.setPosition(120, 10);
    title.setFillColor(sf::Color::Black);

    // Labels
    sf::Text nameLabel("Name:", font, 15);
    nameLabel.setPosition(20, 60);
    nameLabel.setFillColor(sf::Color::Black);

    sf::Text contactLabel("Contact Number:", font, 15);
    contactLabel.setPosition(20, 110);
    contactLabel.setFillColor(sf::Color::Black);

    sf::Text paymentIDLabel("Ticket Payment ID:", font, 15);
    paymentIDLabel.setPosition(20, 160);
    paymentIDLabel.setFillColor(sf::Color::Black);

    // Input field backgrounds
    sf::RectangleShape nameField(sf::Vector2f(250, 25));
    nameField.setPosition(120, 60);
    nameField.setFillColor(sf::Color(230, 230, 230)); // Light gray

    sf::RectangleShape contactField(sf::Vector2f(250, 25));
    contactField.setPosition(120, 110);
    contactField.setFillColor(sf::Color(230, 230, 230));

    sf::RectangleShape paymentField(sf::Vector2f(250, 25));
    paymentField.setPosition(120, 160);
    paymentField.setFillColor(sf::Color(230, 230, 230));

    // Submit button
    sf::RectangleShape submitButton(sf::Vector2f(100, 30));
    submitButton.setFillColor(sf::Color::Green);
    submitButton.setPosition(150, 230);

    sf::Text submitText("Submit", font, 15);
    submitText.setPosition(170, 235);
    submitText.setFillColor(sf::Color::White);

    // Error message
    sf::Text errorMessage("", font, 15);
    errorMessage.setPosition(20, 270);
    errorMessage.setFillColor(sf::Color::Red);

    // Input field texts
    sf::String inputName, inputContact, inputPaymentID;
    sf::Text nameText("", font, 15);
    nameText.setPosition(125, 63);
    nameText.setFillColor(sf::Color::Black);

    sf::Text contactText("", font, 15);
    contactText.setPosition(125, 113);
    contactText.setFillColor(sf::Color::Black);

    sf::Text paymentText("", font, 15);
    paymentText.setPosition(125, 163);
    paymentText.setFillColor(sf::Color::Black);

    // Active field tracking
    enum ActiveField { NAME, CONTACT, PAYMENT_ID, NONE };
    ActiveField activeField = NAME;

    auto setActiveField = [&](ActiveField field) {
        activeField = field;

        nameField.setFillColor(sf::Color(230, 230, 230));
        contactField.setFillColor(sf::Color(230, 230, 230));
        paymentField.setFillColor(sf::Color(230, 230, 230));

        if (activeField == NAME) nameField.setFillColor(sf::Color::White);
        else if (activeField == CONTACT) contactField.setFillColor(sf::Color::White);
        else if (activeField == PAYMENT_ID) paymentField.setFillColor(sf::Color::White);
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
                    else if (activeField == CONTACT && !inputContact.isEmpty()) inputContact.erase(inputContact.getSize() - 1, 1);
                    else if (activeField == PAYMENT_ID && !inputPaymentID.isEmpty()) inputPaymentID.erase(inputPaymentID.getSize() - 1, 1);
                } else if (event.text.unicode < 128 && event.text.unicode >= 32) {
                    if (activeField == NAME) inputName += static_cast<char>(event.text.unicode);
                    else if (activeField == CONTACT) inputContact += static_cast<char>(event.text.unicode);
                    else if (activeField == PAYMENT_ID) inputPaymentID += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(formWindow);

                if (nameField.getGlobalBounds().contains(mousePos.x, mousePos.y)) setActiveField(NAME);
                else if (contactField.getGlobalBounds().contains(mousePos.x, mousePos.y)) setActiveField(CONTACT);
                else if (paymentField.getGlobalBounds().contains(mousePos.x, mousePos.y)) setActiveField(PAYMENT_ID);
                else if (submitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (!inputName.isEmpty() && !inputContact.isEmpty() && !inputPaymentID.isEmpty()) {
                        name = inputName.toAnsiString();
                        contactNumber = inputContact.toAnsiString();
                        paymentID = inputPaymentID.toAnsiString();
                        formWindow.close();
                        return true;
                    } else {
                        // Display error message
                        errorMessage.setString("Please fill all fields!");
                    }
                }
            }
        }

    
        nameText.setString(inputName);
        contactText.setString(inputContact);
        paymentText.setString(inputPaymentID);

    
        formWindow.clear(sf::Color::White);

        formWindow.draw(title);
        formWindow.draw(nameLabel);
        formWindow.draw(contactLabel);
        formWindow.draw(paymentIDLabel);

        formWindow.draw(nameField);
        formWindow.draw(contactField);
        formWindow.draw(paymentField);

        formWindow.draw(nameText);
        formWindow.draw(contactText);
        formWindow.draw(paymentText);

        formWindow.draw(submitButton);
        formWindow.draw(submitText);

        // Draw the error message
        formWindow.draw(errorMessage);

        formWindow.display();
    }

   return false;
}
