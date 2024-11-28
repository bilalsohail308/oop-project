#ifndef MARKETPLACE_SCREEN_H
#define MARKETPLACE_SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Item.h"

class MarketplaceScreen {
private:
    std::vector<Item> items;              // List of items in the marketplace
    sf::Font font;                        // Font for rendering text
    sf::Text title;                       // Marketplace title
    sf::RectangleShape uploadButton;      // Button for uploading new items
    sf::Text uploadText;                  // Text displayed on the upload button
    std::string username;                 // Username of the logged-in user
    float scrollOffset;                   // Offset for scrolling through items
    int boxWidth, boxHeight;              // Dimensions for item boxes
    int nextX, nextY;                     // Coordinates for placing the next item
    const std::string filePath = "C:/Users/LENOVO/OneDrive/Desktop/Cpp/project.cpp/Marketplace/Marketplace.txt"; // Filepath for storing marketplace data
    static const int PADDING = 20;        // Padding between items
    static const float SCROLL_SPEED;      // Scrolling speed for the marketplace view

public:
    // Constructors
    MarketplaceScreen();
    explicit MarketplaceScreen(const std::string& username); // Initialize with a username

    // Rendering and events
    void render(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window, sf::Event& event);

    // File operations
    void saveItemToFile(const Item& item);        // Save a new item to the file
    void loadItemsFromFile();                     // Load all items from the file
    void deleteItem(const std::string& itemName); // Delete an item from the file
    void openItemPreview(const Item& item);
};

#endif // MARKETPLACE_SCREEN_H
