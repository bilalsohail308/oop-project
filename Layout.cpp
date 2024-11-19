// Layout.cpp
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

    // Determine the number of items per row based on the window width
    int numItemsPerRow = std::max(1, maxRowWidth / (Item::BOX_WIDTH + PADDING));

    // Recalculate boxWidth and boxHeight
    boxWidth = (maxRowWidth - (numItemsPerRow + 1) * PADDING) / numItemsPerRow;
    boxHeight = boxWidth; // Keep the boxes square, or adjust as needed

    // Calculate left margin to center the items
    float totalContentWidth = numItemsPerRow * boxWidth + (numItemsPerRow + 1) * PADDING;
    float leftMargin = (maxRowWidth - totalContentWidth) / 2;

    // Reset positions
    nextX = leftMargin + PADDING;
    nextY = 100;

    // Reposition and resize each item
    for (size_t i = 0; i < items.size(); ++i) {
        items[i].box.setSize(sf::Vector2f(boxWidth, boxHeight));
        items[i].box.setPosition(nextX, nextY);

        // Adjust the sprite size and position
        sf::FloatRect spriteBounds = items[i].sprite.getLocalBounds();
        float spriteScaleX = (boxWidth - 20) / spriteBounds.width;
        float spriteScaleY = (boxHeight - 80) / spriteBounds.height;
        float spriteScale = std::min(spriteScaleX, spriteScaleY);
        items[i].sprite.setScale(spriteScale, spriteScale);
        items[i].sprite.setPosition(nextX + 10, nextY + 10);

        // Update nextX and nextY
        nextX += boxWidth + PADDING;
        if ((i + 1) % numItemsPerRow == 0) {
            nextX = leftMargin + PADDING;
            nextY += boxHeight + PADDING;
        }
    }

    // Adjust the Add Item button position
    adjustAddItemButton(window, uploadButton, uploadText, nextY, boxHeight, PADDING);
}
