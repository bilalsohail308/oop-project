#ifndef POSTFEED_H
#define POSTFEED_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Post {
public:
    sf::RectangleShape postBox;
    sf::Text text;
    sf::Sprite image;
    sf::RectangleShape likeButton;
    sf::RectangleShape commentButton;
    sf::Text likeText;

    int likes;

    Post(const std::string& content, const sf::Texture& texture, sf::Font& font, float yPosition);
};

class PostFeed {
private:
    sf::RenderWindow* window;
    sf::Font font;

    // Header Bar
    sf::RectangleShape headerBar;
    sf::Text headerTitle;

    // Post Creation Area
    sf::RectangleShape inputBox;
    sf::Text inputText;
    sf::RectangleShape postButton;

    // Feed
    std::vector<Post> posts;
    sf::Texture postImageTexture;

    // Scrolling
    sf::View feedView;
    float scrollOffset;

public:
    PostFeed(sf::RenderWindow* win);
    void handleEvent(const sf::Event& event);
    void update();
    void draw();
    void createPost(const std::string& content, const sf::Texture& texture);
    void scroll(float offset);
};

#endif // POSTFEED_H
