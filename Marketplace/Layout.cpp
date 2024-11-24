#include "Layout.h"
#include <algorithm>

void adjustAddItemButton(sf::RenderWindow& window, sf::RectangleShape& uploadButton, sf::Text& uploadText, int nextY, int boxHeight, const int PADDING) {
    float buttonWidth = 150;
    float buttonHeight = 40;

    // Center the button horizontally
    float buttonX = (window.getSize().x - buttonWidth) / 2;
    float buttonY = nextY + boxHeight + PADDING;

    uploadButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    uploadButton.setPosition(buttonX, buttonY);
    uploadText.setPosition(buttonX + (buttonWidth - uploadText.getLocalBounds().width) / 2, buttonY + 5);
}

void updateLayout(sf::RenderWindow& window, std::vector<Item>& items, int& boxWidth, int& boxHeight, int& nextX, int& nextY,
                  const int PADDING, sf::RectangleShape& uploadButton, sf::Text& uploadText) {
    int maxRowWidth = window.getSize().x;

    // Determine the number of items per row
    int numItemsPerRow = std::max(1, (maxRowWidth - PADDING) / (Item::BOX_WIDTH + PADDING));

    // Recalculate boxWidth and boxHeight
    boxWidth = std::max(100, (maxRowWidth - (numItemsPerRow + 1) * PADDING) / numItemsPerRow);
    boxHeight = boxWidth; // Keep the boxes square or adjust as needed

    // Calculate left margin for centering
    float totalContentWidth = numItemsPerRow * boxWidth + (numItemsPerRow + 1) * PADDING;
    float leftMargin = std::max((maxRowWidth - totalContentWidth) / 2, 0.0f);

    // Reset positions
    nextX = leftMargin + PADDING;
    nextY = 100;

    // Reposition and resize each item
    for (size_t i = 0; i < items.size(); ++i) {
        items[i].box.setSize(sf::Vector2f(boxWidth, boxHeight));
        items[i].box.setPosition(nextX, nextY);

        // Adjust sprite size and position
        sf::FloatRect spriteBounds = items[i].sprite.getLocalBounds();
        float spriteScale = std::min((boxWidth - 20) / spriteBounds.width, (boxHeight - 80) / spriteBounds.height);
        items[i].sprite.setScale(spriteScale, spriteScale);
        items[i].sprite.setPosition(nextX + 10, nextY + 10);

        // Update nextX and nextY
        nextX += boxWidth + PADDING;
        if ((i + 1) % numItemsPerRow == 0) {
            nextX = leftMargin + PADDING;
            nextY += boxHeight + PADDING;
        }
    }

    // Adjust the "Add Item" button position
    adjustAddItemButton(window, uploadButton, uploadText, nextY, boxHeight, PADDING);
}

void recalculateLayoutAfterDeletion(sf::RenderWindow& window, std::vector<Item>& items, int& boxWidth, int& boxHeight,
                                     int& nextX, int& nextY, const int PADDING, sf::RectangleShape& uploadButton,
                                     sf::Text& uploadText) {
    // Simply call updateLayout to recalculate the entire layout
    updateLayout(window, items, boxWidth, boxHeight, nextX, nextY, PADDING, uploadButton, uploadText);
}
