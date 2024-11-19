// main.cpp
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Item.h"
#include "FormWindow.h"
#include "Layout.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Marketplace", sf::Style::Default);
    sf::Font font;

    // Load the font
    if (!font.loadFromFile("C:/Users/LENOVO/OneDrive/Desktop/Cpp/project.cpp/Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return -1;
    }

    sf::Text title("Bazaar", font, 30);
    title.setPosition(300, 10);

    sf::RectangleShape uploadButton(sf::Vector2f(150, 40));
    uploadButton.setFillColor(sf::Color::Blue);

    sf::Text uploadText("Add Item", font, 20);
    uploadText.setFillColor(sf::Color::White);

    std::vector<Item> items;

    // Layout variables
    const int PADDING = 20;
    int boxWidth = Item::BOX_WIDTH;
    int boxHeight = Item::BOX_HEIGHT;
    int nextX = 0, nextY = 100;

    // Scroll variables
    float scrollOffset = 0;
    const float SCROLL_SPEED = 20.0f;

    // Adjust the layout initially
    updateLayout(window, items, boxWidth, boxHeight, nextX, nextY, PADDING, uploadButton, uploadText);

    // Main Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle window resize
            if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                updateLayout(window, items, boxWidth, boxHeight, nextX, nextY, PADDING, uploadButton, uploadText);
            }

            // Handle mouse wheel scrolling
            if (event.type == sf::Event::MouseWheelScrolled) {
                scrollOffset -= event.mouseWheelScroll.delta * SCROLL_SPEED;

                // Constrain the scroll offset
                float contentHeight = nextY + boxHeight + PADDING + 40; // Include the space for the button
                float maxOffset = std::max(0.0f, contentHeight - static_cast<float>(window.getSize().y));
                scrollOffset = std::clamp(scrollOffset, -maxOffset, 0.0f);
            }

            // Handle mouse click for "Add Item" button
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // Adjust mouse position for scrollOffset
                sf::Vector2f worldPos(mousePos.x, mousePos.y - scrollOffset);
                if (uploadButton.getGlobalBounds().contains(worldPos)) {
                    std::string name, description, imagePath;
                    int price;

                    // Open the form to add a new item
                    if (openFormWindow(name, description, price, imagePath)) {
                        items.emplace_back(name, description, price, imagePath);
                        updateLayout(window, items, boxWidth, boxHeight, nextX, nextY, PADDING, uploadButton, uploadText);
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw static UI elements (title)
        window.draw(title);

        // Adjust and draw the upload button and text
        sf::RectangleShape adjustedUploadButton = uploadButton;
        sf::Text adjustedUploadText = uploadText;
        adjustedUploadButton.move(0, scrollOffset);
        adjustedUploadText.move(0, scrollOffset);
        window.draw(adjustedUploadButton);
        window.draw(adjustedUploadText);

        // Render all items with scrollOffset applied
        for (const auto& item : items) {
            sf::RectangleShape adjustedBox = item.box;
            sf::Sprite adjustedSprite = item.sprite;

            adjustedBox.move(0, scrollOffset);
            adjustedSprite.move(0, scrollOffset);

            // Draw item box and image
            window.draw(adjustedBox);
            window.draw(adjustedSprite);

            // Render item details (name, description, price)
            sf::Text itemName(item.name, font, 15);
            itemName.setPosition(adjustedBox.getPosition().x + 10, adjustedBox.getPosition().y + boxHeight - 70);
            itemName.setFillColor(sf::Color::Black);

            sf::Text itemDescription(item.description, font, 12);
            itemDescription.setPosition(adjustedBox.getPosition().x + 10, adjustedBox.getPosition().y + boxHeight - 50);
            itemDescription.setFillColor(sf::Color::Black);

            sf::Text itemPrice("Price: " + std::to_string(item.price), font, 15);
            itemPrice.setPosition(adjustedBox.getPosition().x + 10, adjustedBox.getPosition().y + boxHeight - 30);
            itemPrice.setFillColor(sf::Color::Black);

            itemName.move(0, scrollOffset);
            itemDescription.move(0, scrollOffset);
            itemPrice.move(0, scrollOffset);

            window.draw(itemName);
            window.draw(itemDescription);
            window.draw(itemPrice);
        }

        window.display();
    }

    return 0;
}
