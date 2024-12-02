#ifndef MARKETPLACE_SCREEN_H
#define MARKETPLACE_SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Item.h"

class MarketplaceScreen {
public:
    std::vector<Item> items;              // List of items in the marketplace
    sf::Font font;                        // Font for rendering text
    sf::Text title;                       // Marketplace title
    sf::RectangleShape uploadButton;      // Button for uploading new items
    sf::Text uploadText;                  // Text displayed on the upload button
    std::string username;                 // Username of the logged-in user
    float scrollOffset;                   // Offset for scrolling through items
    int boxWidth, boxHeight;              // Dimensions for item boxes
    int nextX, nextY;                     // Coordinates for placing the next item
     // Filepath for storing marketplace data
    static const int PADDING = 20;        // Padding between items
    static const float SCROLL_SPEED;      // Scrolling speed for the marketplace view

public:
    // Constructors
    MarketplaceScreen();
    explicit MarketplaceScreen(const std::string& username,std::string f); // Initialize with a username

    // Rendering and events
    void render(sf::RenderWindow& window);
    virtual void handleEvents(sf::RenderWindow& window, sf::Event& event);

    // File operations
    void saveItemToFile(const Item& item,const std::string& filePath);        // Save a new item to the file
    void loadItemsFromFile(const std::string& filePath);                     // Load all items from the file
    void deleteItem(const std::string& itemName); // Delete an item from the file
    void openItemPreview(const Item& item);
};

#endif // MARKETPLACE_SCREEN_H
