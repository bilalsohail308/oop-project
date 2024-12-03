#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <fstream>     // For file streams (std::ifstream, std::ofstream)
#include <sstream>
#include <iostream>
#include "../include/gossip.h"

#include "tinyfiledialog.cpp"
using namespace std;



    Comment::Comment(const std::string& text, float yPosition) {
        font.loadFromFile("../assets/Arial.ttf");

        content.setFont(font);
        content.setString(text);
        content.setCharacterSize(18);
        content.setFillColor(sf::Color::Black);
        content.setPosition(35, yPosition + 10);

        rect.setSize({350, 50});
        rect.setFillColor(sf::Color(240, 240, 240));
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(1);
        rect.setPosition(25, yPosition);
    }




    CommentBox::CommentBox() {
        font.loadFromFile("../assets/Arial.ttf");

        
        background.setSize({400, 600});
        background.setFillColor(sf::Color(200, 200, 200));
        background.setPosition(20, 20);

        
        inputBox.setSize({300, 50});
        inputBox.setFillColor(sf::Color::White);
        inputBox.setOutlineColor(sf::Color::Black);
        inputBox.setOutlineThickness(1);
        inputBox.setPosition(25, 530);

        
        commentButton.setSize({80, 50});
        commentButton.setFillColor(sf::Color(100, 150, 250));
        commentButton.setPosition(335, 530);

        commentButtonText.setFont(font);
        commentButtonText.setString("Comment");
        commentButtonText.setCharacterSize(18);
        commentButtonText.setFillColor(sf::Color::White);
        commentButtonText.setPosition(345, 540);

       
        inputText.setFont(font);
        inputText.setCharacterSize(18);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(30, 540);
    }

    void CommentBox::createComment(const std::string& text) {
        float yPosition = 40 + comments.size() * 60; 
        comments.emplace_back(text, yPosition);
    }

    void CommentBox::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') { 
                if (!inputText.getString().isEmpty()) {
                    std::string str = inputText.getString();
                    str.pop_back();
                    inputText.setString(str);
                }
            } else if (event.text.unicode < 128) { 
                inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                if (commentButton.getGlobalBounds().contains(mousePos)) {
                    if (!inputText.getString().isEmpty()) {
                        createComment(inputText.getString());
                        inputText.setString(""); 
                    }
                }
            }
        }
    }

    void CommentBox::draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(inputBox);
        window.draw(commentButton);
        window.draw(commentButtonText);
        window.draw(inputText);

        for (const auto& comment : comments) {
            window.draw(comment.rect);
            window.draw(comment.content);
        }
    }




Post::Post(const std::string& content, const sf::Texture& texture, double yPosition,const std::string& a)
    : likes(0) {
    


    
    postBox.setSize({750, 150 + 300}); 
    postBox.setFillColor(sf::Color(240, 240, 240));
    postBox.setOutlineColor(sf::Color::Black);
    postBox.setOutlineThickness(1);
    postBox.setPosition(25, yPosition);

    
    fonta.loadFromFile("../assets/Arial.ttf");
    text.setFont(fonta);
    text.setString(a+" : "+content);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    text.setPosition(postBox.getPosition().x + 10, postBox.getPosition().y + 10);

    
            // In Post constructor
        image.setTexture(texture);
        // Resize the image to 300x300 pixels, regardless of its original size
        image.setScale(300.f / texture.getSize().x, 300.f / texture.getSize().y);
        image.setPosition(postBox.getPosition().x + 10, postBox.getPosition().y + 50);

    

    
    likeButton.setSize({80, 30});
    likeButton.setFillColor(sf::Color(100, 149, 237));
    likeButton.setPosition(postBox.getPosition().x + postBox.getSize().x - 90, postBox.getPosition().y + 110 + 300);

    
    likeText.setFont(fonta);
    likeText.setString("Like");
    likeText.setCharacterSize(14);
    likeText.setFillColor(sf::Color::White);
    likeText.setPosition(likeButton.getPosition().x + 20, likeButton.getPosition().y + 5);

    cmntbut.setSize({80, 30});
    cmntbut.setFillColor(sf::Color(100, 149, 237));
    cmntbut.setPosition(postBox.getPosition().x + postBox.getSize().x - 90, postBox.getPosition().y + 70 + 300);

    
    cmnttxt.setFont(fonta);
    cmnttxt.setString("Comments");
    cmnttxt.setCharacterSize(14);
    cmnttxt.setFillColor(sf::Color::White);
    cmnttxt.setPosition(cmntbut.getPosition().x + 20, cmntbut.getPosition().y + 5);
}



PostFeed::PostFeed(sf::RenderWindow* win)
    : window(win), scrollOffset(0), imageLoaded(false), lastWindowSize(win->getSize()) {
    font.loadFromFile("../assets/Arial.ttf");
    filePath="../assets/posts.txt";
    initializeUI();
    loadItemsFromFile();
}

void PostFeed::initializeUI() {
    sf::Vector2u winSize = window->getSize();
    float winWidth = winSize.x;
    float winHeight = winSize.y;
    background.setSize({winWidth,winHeight});
    background.setFillColor(sf::Color(0,0,0));
    headerBar.setSize({winWidth, winHeight * 0.08f});
    headerBar.setFillColor(sf::Color(128, 0, 128));
    headerTitle.setFont(font);
    headerTitle.setString("Gossip");
    headerTitle.setCharacterSize(24);
    headerTitle.setFillColor(sf::Color::White);
    headerTitle.setPosition(10, 10);
    inputBox.setSize({winWidth * 0.93f, winHeight * 0.08f});
    inputBox.setFillColor(sf::Color(255, 255, 255));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(1);
    inputBox.setPosition(winWidth * 0.035f, winHeight * 0.12f);
    inputText.setFont(font);
    inputText.setString("Write something here...");
    inputText.setCharacterSize(18);
    inputText.setFillColor(sf::Color(128, 128, 128));
    inputText.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 10);
    postButton.setSize({winWidth * 0.125f, winHeight * 0.066f});
    postButton.setFillColor(sf::Color(0,128,0));
    postButton.setPosition(winWidth * 0.80f, winHeight * 0.12f);
    postButtontext.setFont(font);
    postButtontext.setString("POST");
    postButtontext.setCharacterSize(17);
    postButtontext.setFillColor(sf::Color::White);
    postButtontext.setPosition(postButton.getPosition().x + 20, postButton.getPosition().y + 5);    
    
}
void PostFeed::saveItemToFile(const std::string& content, const std::string& filepath, const std::string& username) {
    std::ofstream outFile(filePath, std::ios::app); // Open in append mode
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    // Write data in CSV format: username, content, filepath
    outFile << username << "," << content << "," << filepath << "\n";

    outFile.close();
}



void PostFeed::loadItemsFromFile() {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string username, content, filepath;

        // Parse the CSV line
        if (std::getline(ss, username, ',') &&
            std::getline(ss, content, ',') &&
            std::getline(ss, filepath)) {

            // Calculate yPosition dynamically
            double yPosition = posts.empty() ? 110 : posts.back().postBox.getPosition().y + posts.back().postBox.getSize().y + 10;

            // Load the image texture
            sf::Texture newTexture;
            if (newTexture.loadFromFile(filepath)) {
                textures.push_back(std::move(newTexture));
                posts.emplace_back(content, textures.back(), yPosition, username);
            } else {
                std::cerr << "Failed to load texture from " << filepath << std::endl;
            }
        }
    }

    inFile.close();
}

void PostFeed::draw() {
    window->draw(background);
    window->draw(headerBar);
    window->draw(headerTitle);
    window->draw(inputBox);
    window->draw(inputText);
    window->draw(postButton);
    window->draw(postButtontext);
    

    for (const auto& post : posts) {
        window->draw(post.postBox);
        window->draw(post.text);
        window->draw(post.image);
        window->draw(post.likeButton);
        window->draw(post.likeText);
        window->draw(post.cmntbut);
        window->draw(post.cmnttxt);
    }

    
}

void PostFeed::scroll(float offset) {
    scrollOffset += offset;
    feedView.move(0, offset);
    for (auto& post : posts) {
        post.postBox.move(0, offset);
        post.text.move(0, offset);
        post.image.move(0, offset);
        post.likeButton.move(0, offset);
        post.likeText.move(0, offset);
        post.cmntbut.move(0,offset);
        post.cmnttxt.move(0,offset);
    }
}

void PostFeed::handleEvent(const sf::Event& event,const std::string& username) {
    
    if (event.type == sf::Event::Resized) {
        window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        initializeUI();
    } else if (event.type == sf::Event::MouseWheelScrolled) {
        scroll(event.mouseWheelScroll.delta * -30);
    } else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        if (postButton.getGlobalBounds().contains(mousePos)) {
            std::string content = inputText.getString();
            if (content.empty() || content == "Write something here...") {
                std::cout << "Cannot post: content is empty." << std::endl;
                return;
            }

            std::string filePath = openFileDialoga();
            if (!filePath.empty()) {
    sf::Texture newTexture;
    if (newTexture.loadFromFile(filePath)) {
        noofposts++;
        textures.push_back(std::move(newTexture));
        double yPosition = posts.empty() ? 110 : posts.back().postBox.getPosition().y + posts.back().postBox.getSize().y + 10;
        posts.emplace_back(content, textures.back(), yPosition,username);
        saveItemToFile(content, filePath,  username);
        inputText.setString("Write something here...");
        inputText.setFillColor(sf::Color(128, 128, 128));
    } else {
        std::cerr << "Failed to load image." << std::endl;
    }
}
        }

        
        for (auto& post : posts) {
            if (post.cmntbut.getGlobalBounds().contains(mousePos)) {
                
                sf::RenderWindow commentWindow(sf::VideoMode(450, 650), "Comments");
                CommentBox commentBox;

                while (commentWindow.isOpen()) {
                    sf::Event commentEvent;
                    while (commentWindow.pollEvent(commentEvent)) {
                        if (commentEvent.type == sf::Event::Closed) {
                            commentWindow.close();
                        }

                        commentBox.handleEvent(commentEvent, commentWindow);
                    }

                    commentWindow.clear(sf::Color::White);
                    commentBox.draw(commentWindow);
                    commentWindow.display();
                }
                return;
            }
        }
    }else if (inputBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            if (inputText.getString() == "Write something here...") {
                inputText.setString("");
                inputText.setFillColor(sf::Color::Black);
            }
        }
    else if (event.type == sf::Event::TextEntered) {
        if (inputBox.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x,
                                                sf::Mouse::getPosition(*window).y)) {
            if (event.text.unicode == 8 && inputText.getString().getSize() > 0) {  
                inputText.setString(inputText.getString().substring(0, inputText.getString().getSize() - 1));
            } else if (event.text.unicode < 128 && event.text.unicode != 8) {  
                inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
            }
        }
    }}


