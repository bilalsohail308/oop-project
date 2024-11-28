#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "tinyfiledialog.cpp"
using namespace std;

class Comment {
public:
    sf::RectangleShape rect;
    sf::Text content;
    sf::Font font;

    Comment(const std::string& text, float yPosition) {
        font.loadFromFile("arial.ttf");

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

    CommentBox() {
        font.loadFromFile("F:\\sem3\\OOP\\oop-project\\Gossip\\arial.ttf");

        
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

    void createComment(const std::string& text) {
        float yPosition = 40 + comments.size() * 60; 
        comments.emplace_back(text, yPosition);
    }

    void handleEvent(const sf::Event& event, sf::RenderWindow& window) {
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

    void draw(sf::RenderWindow& window) {
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
};

class Post {
public:
    Post(const std::string& content, const sf::Texture& texture, double y,string a );

    sf::RectangleShape postBox;
    sf::Text text;
    sf::Font fonta;
    sf::Sprite image;
    sf::RectangleShape likeButton ,cmntbut;
    sf::Text likeText,cmnttxt;
    
    int likes;
};

Post::Post(const std::string& content, const sf::Texture& texture, double yPosition,string a)
    : likes(0) {
    
;

    
    postBox.setSize({750, 150}); 
    postBox.setFillColor(sf::Color(240, 240, 240));
    postBox.setOutlineColor(sf::Color::Black);
    postBox.setOutlineThickness(1);
    postBox.setPosition(25, yPosition);

    
    fonta.loadFromFile("F:\\sem3\\OOP\\oop-project\\Gossip\\arial.ttf");
    text.setFont(fonta);
    text.setString(a+" : "+content);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    text.setPosition(postBox.getPosition().x + 10, postBox.getPosition().y + 10);

    
    image.setTexture(texture);
    image.setScale(0.5f, 0.5f);
    image.setPosition(postBox.getPosition().x + 10, postBox.getPosition().y + 50);
    

    
    likeButton.setSize({80, 30});
    likeButton.setFillColor(sf::Color(100, 149, 237));
    likeButton.setPosition(postBox.getPosition().x + postBox.getSize().x - 90, postBox.getPosition().y + 110);

    
    likeText.setFont(fonta);
    likeText.setString("Like");
    likeText.setCharacterSize(14);
    likeText.setFillColor(sf::Color::White);
    likeText.setPosition(likeButton.getPosition().x + 20, likeButton.getPosition().y + 5);

    cmntbut.setSize({80, 30});
    cmntbut.setFillColor(sf::Color(100, 149, 237));
    cmntbut.setPosition(postBox.getPosition().x + postBox.getSize().x - 90, postBox.getPosition().y + 70);

    
    cmnttxt.setFont(fonta);
    cmnttxt.setString("Comments");
    cmnttxt.setCharacterSize(14);
    cmnttxt.setFillColor(sf::Color::White);
    cmnttxt.setPosition(cmntbut.getPosition().x + 20, cmntbut.getPosition().y + 5);
}

class PostFeed {
public:
    PostFeed(sf::RenderWindow* win);
    

    void draw();
    void handleEvent(const sf::Event& event,string a);
    
    void scroll(float offset);
    void createPost(const std::string& content, const sf::Texture& texture,int ne,string a);
    

private:
    sf::RenderWindow* window;
    sf::View feedView;
    sf::Font font;
    int noofposts{0};
    sf::RectangleShape headerBar;
    sf::Text headerTitle;
    sf::RectangleShape inputBox, background;
    sf::Text inputText;
    sf::RectangleShape postButton;
    sf::RectangleShape navigationBar;
    sf::Text navProfile, navFeed, navWatch,postButtontext;

   
    std::vector<Post> posts;
    sf::Texture postImageTexture;
    std::vector<sf::Texture> textures;
    float scrollOffset;
    bool imageLoaded;
    sf::Vector2u lastWindowSize;

    void initializeUI();
};

PostFeed::PostFeed(sf::RenderWindow* win)
    : window(win), scrollOffset(0), imageLoaded(false), lastWindowSize(win->getSize()) {
    font.loadFromFile("F:\\sem3\\OOP\\oop-project\\Gossip\\arial.ttf");
    initializeUI();
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
    navigationBar.setSize({winWidth, winHeight * 0.08f});
    navigationBar.setFillColor(sf::Color(128, 0, 128));
    navigationBar.setPosition(0, winHeight - winHeight * 0.08f);
    navProfile.setFont(font);
    navProfile.setString("MARKETPLACE");
    navProfile.setCharacterSize(18);
    navProfile.setFillColor(sf::Color::White);
    navProfile.setPosition(winWidth * 0.02f, winHeight - winHeight * 0.06f);
    navFeed.setFont(font);
    navFeed.setString("Upcoming EVENTS");
    navFeed.setCharacterSize(18);
    navFeed.setFillColor(sf::Color::White);
    navFeed.setPosition(winWidth * 0.20f, winHeight - winHeight * 0.06f);
    navWatch.setFont(font);
    navWatch.setString("Leaderboard");
    navWatch.setCharacterSize(18);
    navWatch.setFillColor(sf::Color::White);
    navWatch.setPosition(winWidth * 0.44f, winHeight - winHeight * 0.06f);
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

    window->draw(navigationBar);
    window->draw(navProfile);
    window->draw(navFeed);
    window->draw(navWatch);
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

void PostFeed::handleEvent(const sf::Event& event,string us) {
    
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

            std::string filePath = openFileDialog();
            if (!filePath.empty()) {
    sf::Texture newTexture;
    if (newTexture.loadFromFile(filePath)) {
        noofposts++;
        textures.push_back(std::move(newTexture));
        double yPosition = posts.empty() ? 25 : posts.back().postBox.getPosition().y + posts.back().postBox.getSize().y + 10;
        posts.emplace_back(content, textures.back(), yPosition,us);
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

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Post Feed");
    PostFeed feed(&window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            feed.handleEvent(event,"awais");
        }

        window.clear(sf::Color::White);
        feed.draw();
        window.display();
    }

    return 0;
}
