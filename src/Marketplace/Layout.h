#ifndef LAYOUT_H
#define LAYOUT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h"

// Adjusts the "Add Item" button position
void adjustAddItemButton(sf::RenderWindow& window, sf::RectangleShape& uploadButton, sf::Text& uploadText, int nextY, int boxHeight, const int PADDING);

// Updates the layout of the items and the "Add Item" button
void updateLayout(sf::RenderWindow& window,
                  std::vector<Item>& items,
                  int& boxWidth,
                  int& boxHeight,
                  int& nextX,
                  int& nextY,
                  const int PADDING,
                  sf::RectangleShape& uploadButton,
                  sf::Text& uploadText);

#endif // LAYOUT_H
