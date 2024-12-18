#ifndef POSTFEED_H
#define POSTFEED_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Comment {
public:
    sf::RectangleShape rect;
    sf::Text content;
    sf::Font font;

    Comment(const std::string& text, float yPosition);
};

class CommentBox {
public:
    sf::RectangleShape background;
    sf::RectangleShape inputBox;
    sf::RectangleShape commentButton;
    sf::Text commentButtonText;
    sf::Text inputText;
    sf::Font font;
    std::vector<Comment> comments;

    CommentBox();

    void createComment(const std::string& text);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

class Post {
public:
    sf::RectangleShape postBox;
    sf::Text text;
    sf::Font fonta;
    sf::Sprite image;
    sf::RectangleShape likeButton, cmntbut;
    sf::Text likeText, cmnttxt;
    int likes;

    Post(const std::string& content, const sf::Texture& texture, double yPosition, const std::string& username);
};

class PostFeed {
public:
    PostFeed(sf::RenderWindow* win);
    
    void saveItemToFile(const std::string& content, const std::string& filepath,  const std::string& username);
    void loadItemsFromFile();
    void draw();
    void handleEvent(const sf::Event& event, const std::string& username);
    void scroll(float offset);
    void createPost(const std::string& content, const sf::Texture& texture, int ne, const std::string& username);

private:
    sf::RenderWindow* window;
    std::string filePath;
    sf::View feedView;
    sf::Font font;
    int noofposts;
    sf::RectangleShape headerBar;
    sf::Text headerTitle;
    sf::RectangleShape inputBox, background;
    sf::Text inputText;
    sf::RectangleShape postButton;
    sf::Text postButtontext;

    std::vector<Post> posts;
    sf::Texture postImageTexture;
    std::vector<sf::Texture> textures;
    float scrollOffset;
    bool imageLoaded;
    sf::Vector2u lastWindowSize;

    void initializeUI();
};

#endif // POSTFEED_H
