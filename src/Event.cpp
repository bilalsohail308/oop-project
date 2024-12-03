#include "../include/EventScreen.h"
#include "../include/FormWindow.h"
#include "../include/Layout.h"
#include <iostream>

// Constructor
EventScreen::EventScreen(const std::string& username)
    : MarketplaceScreen(username,"../assets/event.txt") {
    title.setString("Events"); // Adjust the title for the event screen
    uploadText.setString("Add Event");
    std::cout << "EventScreen initialized for user: " << username << "\n";
}

// Handle events
void EventScreen::handleEvents(sf::RenderWindow& window, sf::Event& event) {
    // Handle window close event
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    // Handle window resize event
    if (event.type == sf::Event::Resized) {
        // Update layout to adapt to the new window size
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        updateLayout(window, items, boxWidth, boxHeight, nextX, nextY, PADDING, uploadButton, uploadText);
    }

    // Handle mouse wheel scrolling for item list
    if (event.type == sf::Event::MouseWheelScrolled) {
        scrollOffset -= event.mouseWheelScroll.delta * SCROLL_SPEED;

        // Constrain the scroll offset to avoid overscrolling
        float contentHeight = nextY + boxHeight + PADDING + 40; // Total content height including button space
        float maxOffset = std::max(0.0f, contentHeight - static_cast<float>(window.getSize().y));
        scrollOffset = std::clamp(scrollOffset, -maxOffset, 0.0f);
    }

    // Handle mouse button press events
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos(mousePos.x, mousePos.y - scrollOffset);

        // Check if an item's image is clicked
        for (const auto& item : items) {
            if (item.sprite.getGlobalBounds().contains(worldPos)) {
                openItemPreview(item); // Open the preview window for the clicked item
                return; // Exit once the preview is opened
            }
        }

        // Check if the "Add Item" button is clicked
        if (uploadButton.getGlobalBounds().contains(worldPos)) {
            std::string name, description;
            std::vector<std::string> imagePaths;
            int price;

            if (openEFormWindow(name, description, price, imagePaths)) {
        std::string uniqueId = generateUniqueId(); // Generate unique ID
        Item newItem(uniqueId, name, description, price, imagePaths, username);
        items.emplace_back(newItem);

        saveItemToFile(newItem,"../assets/event.txt"); // Save to file
     updateLayout(window, items, boxWidth, boxHeight, nextX, nextY, PADDING, uploadButton, uploadText);
}
        }
    }
}
