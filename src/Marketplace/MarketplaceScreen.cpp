#include "MarketplaceScreen.h"
#include "Layout.h"
#include "FormWindow.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <random>
#include "Item.h"
#include <random>
#include "utils.h"

const float MarketplaceScreen::SCROLL_SPEED = 20.0f;

// Constructor
MarketplaceScreen::MarketplaceScreen(const std::string& username)
    : username(username), scrollOffset(0), boxWidth(Item::BOX_WIDTH), boxHeight(Item::BOX_HEIGHT), nextX(0), nextY(100) {
    if (!font.loadFromFile("C:/Users/LENOVO/OneDrive/Desktop/Cpp/project.cpp/Marketplace/Arial.ttf")) {
        std::cerr << "Error: Could not load font!\n";
    }

    loadItemsFromFile(); // Load items during initialization
    std::cout << "MarketplaceScreen initialized for user: " << username << "\n";


    // Title
    title.setFont(font);
    title.setString("Bazaar");
    title.setCharacterSize(30);
    title.setPosition(300, 10);

    // Upload Button
    uploadButton.setSize(sf::Vector2f(150, 40));
    uploadButton.setFillColor(sf::Color::Blue);

    // Upload Button Text
    uploadText.setFont(font);
    uploadText.setString("Add Item");
    uploadText.setCharacterSize(20);
    uploadText.setFillColor(sf::Color::White);

    // Calculate initial layout
    sf::RenderWindow tempWindow(sf::VideoMode(800, 600), "Temp Window"); // Temporary window for layout calculations
    updateLayout(tempWindow, items, boxWidth, boxHeight, nextX, nextY, PADDING, uploadButton, uploadText);
}

void MarketplaceScreen::handleEvents(sf::RenderWindow& window, sf::Event& event) {
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

            if (openFormWindow(name, description, price, imagePaths)) {
        std::string uniqueId = generateUniqueId(); // Generate unique ID
        Item newItem(uniqueId, name, description, price, imagePaths, username);
        items.emplace_back(newItem);

        saveItemToFile(newItem); // Save to file
     updateLayout(window, items, boxWidth, boxHeight, nextX, nextY, PADDING, uploadButton, uploadText);
}
        }
    }
}


void MarketplaceScreen::deleteItem(const std::string& uniqueId) {
    std::cout << "Attempting to delete item with ID: " << uniqueId << "\n";

    // Find the item in memory
    auto it = std::find_if(items.begin(), items.end(),
                           [&](const Item& item) { return item.uniqueId == uniqueId; });

    if (it != items.end()) {
        std::cout << "Item found in memory: " << it->uniqueId << ", deleting...\n";
        items.erase(it); // Remove the item from memory

        // Rewrite the file
        std::ofstream outFile(filePath);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file for writing.\n";
            return;
        }

        for (const auto& item : items) {
            outFile << item.uniqueId << "," // Save the unique ID
                    << item.owner << ","
                    << item.name << ","
                    << item.description << ","
                    << item.price << ",";

            for (size_t i = 0; i < item.imagePaths.size(); ++i) {
                outFile << item.imagePaths[i];
                if (i != item.imagePaths.size() - 1) {
                    outFile << ";";
                }
            }

            outFile << "\n"; // End the line for the current item
        }

        outFile.close();
        std::cout << "Item with ID " << uniqueId << " deleted successfully.\n";

        // Recalculate layout to avoid empty spaces
        sf::RenderWindow tempWindow(sf::VideoMode(800, 600), "Temp Window"); // Temporary window
        updateLayout(tempWindow, items, boxWidth, boxHeight, nextX, nextY, PADDING, uploadButton, uploadText);
    } else {
        std::cerr << "Error: Item with ID " << uniqueId << " not found in memory.\n";
    }
}

void MarketplaceScreen::saveItemToFile(const Item& item) {
    std::ofstream outFile("C:/Users/LENOVO/OneDrive/Desktop/Cpp/project.cpp/Marketplace/Marketplace.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    outFile << item.uniqueId << "," // Save the unique ID
            << item.owner << ","
            << item.name << ","
            << item.description << ","
            << item.price << ",";

    for (size_t i = 0; i < item.imagePaths.size(); ++i) {
        outFile << item.imagePaths[i];
        if (i != item.imagePaths.size() - 1) {
            outFile << ";"; // Separate image paths with a semicolon
        }
    }

    outFile << "\n";
    outFile.close();
}



void MarketplaceScreen::loadItemsFromFile() {
    std::cout << "Loading items from file...\n";
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for reading.\n";
        return;
    }

    items.clear(); // Clear current items before loading new ones

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string uniqueId, owner, name, description, imagePathGroup;
        int price;

        // Parse the file format with the unique ID
        if (std::getline(ss, uniqueId, ',') &&
            std::getline(ss, owner, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, description, ',') &&
            ss >> price && ss.ignore() &&
            std::getline(ss, imagePathGroup)) {
            
            // Split the `imagePathGroup` into multiple paths
            std::vector<std::string> imagePaths;
            std::stringstream pathStream(imagePathGroup);
            std::string path;
            while (std::getline(pathStream, path, ';')) {
                imagePaths.push_back(path);
            }

            // Create and add the new item with the unique ID
            Item newItem(uniqueId, name, description, price, imagePaths, owner);
            items.emplace_back(newItem);
            std::cout << "Loaded item: " << name << " by " << owner << " with " 
                      << imagePaths.size() << " images (ID: " << uniqueId << ").\n"; // Debug log
        }
    }

    inFile.close();
}

void MarketplaceScreen::openItemPreview(const Item& item) {
    sf::RenderWindow previewWindow(sf::VideoMode(800, 600), "Item Preview");
    sf::Font font;

    if (!font.loadFromFile("C:/Users/LENOVO/OneDrive/Desktop/Cpp/project.cpp/Marketplace/Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return;
    }

    sf::Text itemName("Name: " + item.name, font, 20);
    itemName.setPosition(20, 20);
    itemName.setFillColor(sf::Color::Black);

    sf::Text itemDescription("Description: " + item.description, font, 18);
    itemDescription.setPosition(20, 60);
    itemDescription.setFillColor(sf::Color::Black);

    sf::Text itemPrice("Price: " + std::to_string(item.price), font, 20);
    itemPrice.setPosition(20, 100);
    itemPrice.setFillColor(sf::Color::Black);

    sf::Text ownerText("Posted by: " + item.owner, font, 18);
    ownerText.setPosition(20, 140);
    ownerText.setFillColor(sf::Color::Black);

    int currentImageIndex = 0; // Start with the first image
    sf::Texture currentTexture;
    sf::Sprite imageSprite;

    // Load and render the image
    auto loadImage = [&](int index) {
        if (index >= 0 && index < item.imagePaths.size()) {
            if (currentTexture.loadFromFile(item.imagePaths[index])) {
                imageSprite.setTexture(currentTexture);

                const float boxWidth = 500.0f;
                const float boxHeight = 300.0f;

                sf::RectangleShape imageBox(sf::Vector2f(boxWidth, boxHeight));
                imageBox.setFillColor(sf::Color(230, 230, 230)); // Light gray
                imageBox.setOutlineColor(sf::Color::Black);
                imageBox.setOutlineThickness(2.0f);

                imageBox.setPosition(
                    (previewWindow.getSize().x - boxWidth) / 2.0f,
                    (previewWindow.getSize().y - boxHeight) / 2.0f
                );

                float scaleX = boxWidth / currentTexture.getSize().x;
                float scaleY = boxHeight / currentTexture.getSize().y;
                float scale = std::min(scaleX, scaleY);

                imageSprite.setScale(scale, scale);

                float scaledWidth = currentTexture.getSize().x * scale;
                float scaledHeight = currentTexture.getSize().y * scale;
                imageSprite.setPosition(
                    imageBox.getPosition().x + (boxWidth - scaledWidth) / 2.0f,
                    imageBox.getPosition().y + (boxHeight - scaledHeight) / 2.0f
                );

                previewWindow.clear(sf::Color::White);
                previewWindow.draw(imageBox);
                previewWindow.draw(imageSprite);
                previewWindow.display();
            } else {
                std::cerr << "Error: Unable to load image: " << item.imagePaths[index] << std::endl;
            }
        }
    };

    loadImage(currentImageIndex);

    // Action buttons
    sf::RectangleShape actionButton(sf::Vector2f(150, 40));
    actionButton.setFillColor(sf::Color::Blue);

    sf::RectangleShape closeButton(sf::Vector2f(100, 40));
    closeButton.setFillColor(sf::Color::Red);

    sf::Text actionButtonText("", font, 20);
    actionButtonText.setFillColor(sf::Color::White);

    sf::Text closeButtonText("Close", font, 20);
    closeButtonText.setFillColor(sf::Color::White);

    // Button positioning
    auto positionButtons = [&]() {
        closeButton.setPosition(650, 520);
        closeButtonText.setPosition(closeButton.getPosition().x + 15, closeButton.getPosition().y + 5);

        actionButton.setPosition(500, 520);
        actionButtonText.setPosition(actionButton.getPosition().x + 10, actionButton.getPosition().y + 5);
    };

    // Set button text based on ownership
    if (item.owner == username) {
        actionButtonText.setString("Delete");
    } else {
        actionButtonText.setString("Contact");
    }

    positionButtons();

    // Navigation arrows
    sf::RectangleShape leftArrow(sf::Vector2f(50, 50));
    leftArrow.setFillColor(sf::Color::Blue);
    leftArrow.setPosition(50, 500);

    sf::Text leftArrowText("<", font, 30);
    leftArrowText.setFillColor(sf::Color::White);
    leftArrowText.setPosition(65, 505);

    sf::RectangleShape rightArrow(sf::Vector2f(50, 50));
    rightArrow.setFillColor(sf::Color::Blue);
    rightArrow.setPosition(700, 500);

    sf::Text rightArrowText(">", font, 30);
    rightArrowText.setFillColor(sf::Color::White);
    rightArrowText.setPosition(715, 505);

    while (previewWindow.isOpen()) {
        sf::Event event;
        while (previewWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                previewWindow.close();
            }

            // Handle navigation
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(previewWindow);

                if (leftArrow.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (currentImageIndex > 0) {
                        currentImageIndex--;
                        loadImage(currentImageIndex);
                    }
                } else if (rightArrow.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (currentImageIndex < item.imagePaths.size() - 1) {
                        currentImageIndex++;
                        loadImage(currentImageIndex);
                    }
                }

                if (actionButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (item.owner == username) {
                        // Delete item
                        deleteItem(item.uniqueId); // Pass uniqueId to delete
                        previewWindow.close();
                    } else {
                        // Contact owner
                        std::cout << "Contacting owner: " << item.owner << std::endl;
                    }
                }

                if (closeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    previewWindow.close();
                }
            }
        }

        previewWindow.clear(sf::Color::White);

        previewWindow.draw(itemName);
        previewWindow.draw(itemDescription);
        previewWindow.draw(itemPrice);
        previewWindow.draw(ownerText);

        if (currentTexture.getSize().x > 0) {
            previewWindow.draw(imageSprite);
        }

        if (currentImageIndex > 0) {
            previewWindow.draw(leftArrow);
            previewWindow.draw(leftArrowText);
        }
        if (currentImageIndex < item.imagePaths.size() - 1) {
            previewWindow.draw(rightArrow);
            previewWindow.draw(rightArrowText);
        }

        previewWindow.draw(closeButton);
        previewWindow.draw(closeButtonText);
        previewWindow.draw(actionButton);
        previewWindow.draw(actionButtonText);

        previewWindow.display();
    }
}

// Render the marketplace screen
void MarketplaceScreen::render(sf::RenderWindow& window) {
    // Draw the title
    window.draw(title);

    // Adjust and draw the upload button
    sf::RectangleShape adjustedUploadButton = uploadButton;
    sf::Text adjustedUploadText = uploadText;

    adjustedUploadButton.move(0, scrollOffset);
    adjustedUploadText.move(0, scrollOffset);

    window.draw(adjustedUploadButton);
    window.draw(adjustedUploadText);

    // Render items
    for (const auto& item : items) {
        // Adjust the box and sprite for scrolling
        sf::RectangleShape adjustedBox = item.box;
        sf::Sprite adjustedSprite = item.sprite;

        adjustedBox.move(0, scrollOffset);
        adjustedSprite.move(0, scrollOffset);

        window.draw(adjustedBox);
        window.draw(adjustedSprite);

        // Set text relative to the adjusted box position
        sf::Text itemName(item.name, font, 15);
        itemName.setPosition(adjustedBox.getPosition().x + 10, adjustedBox.getPosition().y + 150); // Below the image
        itemName.setFillColor(sf::Color::Black);

        sf::Text itemDescription(item.description, font, 12);
        itemDescription.setPosition(adjustedBox.getPosition().x + 10, adjustedBox.getPosition().y + 170); // Below the name
        itemDescription.setFillColor(sf::Color::Black);

        sf::Text itemPrice("Price: " + std::to_string(item.price), font, 15);
        itemPrice.setPosition(adjustedBox.getPosition().x + 10, adjustedBox.getPosition().y + 190); // Below the description
        itemPrice.setFillColor(sf::Color::Black);

        sf::Text ownerText("Posted by: " + item.owner, font, 12);
        ownerText.setPosition(adjustedBox.getPosition().x + 10, adjustedBox.getPosition().y + adjustedBox.getSize().y - 30); // Near the bottom of the box
        ownerText.setFillColor(sf::Color::Black);

        // Draw all text elements
        window.draw(itemName);
        window.draw(itemDescription);
        window.draw(itemPrice);
        window.draw(ownerText);
    }
}
