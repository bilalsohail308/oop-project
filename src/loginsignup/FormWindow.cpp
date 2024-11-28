#include "FormWindow.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cctype>
#include "FileDialog.h"

bool openEventFormWindow(std::string& name, std::string& description, std::string& date, std::string& venue, std::string& imagePath) {
    sf::RenderWindow formWindow(sf::VideoMode(400, 450), "Add Event");
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return false;
    }

    // Title
    sf::Text title("Add New Event", font, 20);
    title.setPosition(120, 10);
    title.setFillColor(sf::Color::Black);

    // Labels
    sf::Text labels[5] = {
        {"Name:", font, 15},
        {"Description:", font, 15},
        {"Date:", font, 15},
        {"Venue:", font, 15},
        {"Image:", font, 15}
    };

    float labelY[5] = {60, 110, 160, 210, 260};
    for (int i = 0; i < 5; ++i) {
        labels[i].setPosition(20, labelY[i]);
        labels[i].setFillColor(sf::Color::Black);
    }

    // Input fields
    sf::RectangleShape fields[4];
    sf::String inputs[4];
    sf::Text texts[4];

    for (int i = 0; i < 4; ++i) {
        fields[i].setSize(sf::Vector2f(250, 25));
        fields[i].setPosition(120, labelY[i]);
        fields[i].setFillColor(sf::Color(230, 230, 230));

        texts[i].setFont(font);
        texts[i].setCharacterSize(15);
        texts[i].setPosition(125, labelY[i] + 5);
        texts[i].setFillColor(sf::Color::Black);
    }

    // Image button
    sf::RectangleShape imageButton(sf::Vector2f(120, 30));
    imageButton.setPosition(120, 260);
    imageButton.setFillColor(sf::Color::Blue);

    sf::Text imageButtonText("Choose Image", font, 15);
    imageButtonText.setPosition(125, 265);
    imageButtonText.setFillColor(sf::Color::White);

    sf::Text imagePathText("", font, 12);
    imagePathText.setPosition(20, 310);
    imagePathText.setFillColor(sf::Color::Black);

    // Submit button
    sf::RectangleShape submitButton(sf::Vector2f(100, 30));
    submitButton.setPosition(150, 400);
    submitButton.setFillColor(sf::Color::Blue);

    sf::Text submitText("Submit", font, 15);
    submitText.setPosition(170, 405);
    submitText.setFillColor(sf::Color::White);

    enum ActiveField { NAME, DESCRIPTION, DATE, VENUE, NONE };
    ActiveField activeField = NAME;

    auto setActiveField = [&](ActiveField field) {
        activeField = field;
        for (auto& field : fields)
            field.setFillColor(sf::Color(230, 230, 230)); // Reset colors
        if (field != NONE)
            fields[field].setFillColor(sf::Color::White); // Highlight active
    };

    setActiveField(NAME); // Default active field

    while (formWindow.isOpen()) {
        sf::Event event;
        while (formWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                formWindow.close();
                return false; // Form closed
            }

            // Handle text input
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Backspace
                    if (activeField != NONE && !inputs[activeField].isEmpty())
                        inputs[activeField].erase(inputs[activeField].getSize() - 1, 1);
                } else if (event.text.unicode < 128) { // ASCII characters
                    if (activeField != NONE)
                        inputs[activeField] += static_cast<char>(event.text.unicode);
                }
            }

            // Handle mouse click
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(formWindow);

                for (int i = 0; i < 4; ++i) {
                    if (fields[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        setActiveField(static_cast<ActiveField>(i));
                    }
                }

                if (imageButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Open file dialog
                    std::string selectedImage = openFileDialog();
                    if (!selectedImage.empty()) {
                        imagePath = selectedImage;
                        imagePathText.setString("Image: " + selectedImage);
                    }
                }

                if (submitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Submit logic
                    if (!inputs[0].isEmpty() && !inputs[1].isEmpty() && !inputs[2].isEmpty() && !inputs[3].isEmpty() && !imagePath.empty()) {
                        name = inputs[0].toAnsiString();
                        description = inputs[1].toAnsiString();
                        date = inputs[2].toAnsiString();
                        venue = inputs[3].toAnsiString();
                        formWindow.close();
                        return true; // Successful submission
                    } else {
                        std::cerr << "All fields must be filled!" << std::endl;
                    }
                }
            }
        }

        // Update displayed text
        for (int i = 0; i < 4; ++i) {
            texts[i].setString(inputs[i]);
        }

        // Render form
        formWindow.clear(sf::Color::White);
        formWindow.draw(title);

        for (auto& label : labels)
            formWindow.draw(label);

        for (auto& field : fields)
            formWindow.draw(field);

        for (auto& text : texts)
            formWindow.draw(text);

        formWindow.draw(imageButton);
        formWindow.draw(imageButtonText);
        formWindow.draw(imagePathText);
        formWindow.draw(submitButton);
        formWindow.draw(submitText);

        formWindow.display();
    }

    return false;
}
