#ifndef MANAGE_EVENTS_H
#define MANAGE_EVENTS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Event.h"

void handleEvents(sf::RenderWindow& window, std::vector<Event>& events);
void renderUI(sf::RenderWindow& window, std::vector<Event>& events, sf::Font& font);
bool openEventFormWindow(std::string& name, std::string& description, std::string& date, std::string& venue, std::string& imagePath);

#endif
