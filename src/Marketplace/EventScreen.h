#ifndef EVENTSCREEN_H
#define EVENTSCREEN_H

#include "MarketplaceScreen.h"

class EventScreen : public MarketplaceScreen {
public:
    EventScreen(const std::string& username);
    

    void handleEvents(sf::RenderWindow& window, sf::Event& event) override;

private:
    
};

#endif // EVENTSCREEN_H
