
#include "AuthScreen.h"
#include "FileDialog.h" 
#include "User.h"
#include <unordered_map>
#include <iostream>
#include <string>

void AuthScreen::showDialogBox(sf::RenderWindow& parentWindow, const std::string& message, const std::string& title) {
    sf::RenderWindow dialogBox(sf::VideoMode(300, 150), title, sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("F:\\sem3\\OOP\\oop-project\\src\\Marketplace\\Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return;
    }

    sf::Text dialogMessage(message, font, 15);
    dialogMessage.setPosition(20, 50);
    dialogMessage.setFillColor(sf::Color::Black);

    sf::RectangleShape okButton(sf::Vector2f(80, 30));
    okButton.setPosition(110, 100);
    okButton.setFillColor(sf::Color::Blue);

    sf::Text okButtonText("OK", font, 15);
    okButtonText.setPosition(135, 105);
    okButtonText.setFillColor(sf::Color::White);

    while (dialogBox.isOpen()) {
        sf::Event event;
        while (dialogBox.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                dialogBox.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(dialogBox);
                if (okButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    dialogBox.close();
                }
            }
        }

        dialogBox.clear(sf::Color::White);
        dialogBox.draw(dialogMessage);
        dialogBox.draw(okButton);
        dialogBox.draw(okButtonText);
        dialogBox.display();
    }
}

bool AuthScreen::loginScreen(sf::RenderWindow& window, const std::string& filePath, std::string& username, std::string& batch, std::string& major) {
    sf::Font font;
    if (!font.loadFromFile("F:\\sem3\\OOP\\oop-project\\src\\Marketplace\\Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return false;
    }
    std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> users;

     if (!User::loadUsersWithDetails(filePath, users)) {
        AuthScreen::showDialogBox(window, "Error loading user data.", "Error");
        return false;
    }
    
    

    // UI Elements
    sf::Text title("HUBAZAAR", font, 30);
    title.setPosition(150, 50);
    title.setFillColor(sf::Color::Black);

    sf::Text usernameLabel("Username:", font, 15);
    usernameLabel.setPosition(50, 150);
    usernameLabel.setFillColor(sf::Color::Black);

    sf::Text passwordLabel("Password:", font, 15);
    passwordLabel.setPosition(50, 200);
    passwordLabel.setFillColor(sf::Color::Black);

    sf::RectangleShape usernameField(sf::Vector2f(200, 25));
    usernameField.setPosition(150, 150);
    usernameField.setFillColor(sf::Color(230, 230, 230));

    sf::RectangleShape passwordField(sf::Vector2f(200, 25));
    passwordField.setPosition(150, 200);
    passwordField.setFillColor(sf::Color(230, 230, 230));

    sf::RectangleShape loginButton(sf::Vector2f(100, 30));
    loginButton.setPosition(150, 250);
    loginButton.setFillColor(sf::Color::Blue);

    sf::Text loginButtonText("Login", font, 15);
    loginButtonText.setPosition(175, 255);
    loginButtonText.setFillColor(sf::Color::White);

    sf::RectangleShape signupButton(sf::Vector2f(100, 30));
    signupButton.setPosition(150, 300);
    signupButton.setFillColor(sf::Color::Green);

    sf::Text signupButtonText("Signup", font, 15);
    signupButtonText.setPosition(175, 305);
    signupButtonText.setFillColor(sf::Color::White);

    sf::String inputUsername, inputPassword;
    sf::Text usernameText("", font, 15);
    usernameText.setPosition(155, 155);
    usernameText.setFillColor(sf::Color::Black);

    sf::Text passwordText("", font, 15);
    passwordText.setPosition(155, 205);
    passwordText.setFillColor(sf::Color::Black);

    

    // Active field management
    enum ActiveField
    {
        NONE,
        USERNAME,
        PASSWORD
    };
    ActiveField activeField = NONE;

    auto setActiveField = [&](ActiveField field)
    {
        activeField = field;
        usernameField.setFillColor(sf::Color(230, 230, 230));
        passwordField.setFillColor(sf::Color(230, 230, 230));

        if (activeField == USERNAME)
            usernameField.setFillColor(sf::Color::White);
        if (activeField == PASSWORD)
            passwordField.setFillColor(sf::Color::White);
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }

            // Handle text input
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b')
                { // Handle backspace
                    if (activeField == USERNAME && !inputUsername.isEmpty())
                        inputUsername.erase(inputUsername.getSize() - 1, 1);
                    else if (activeField == PASSWORD && !inputPassword.isEmpty())
                        inputPassword.erase(inputPassword.getSize() - 1, 1);
                }
                else if (event.text.unicode < 128)
                { // Handle normal input
                    if (activeField == USERNAME)
                        inputUsername += static_cast<char>(event.text.unicode);
                    else if (activeField == PASSWORD)
                        inputPassword += static_cast<char>(event.text.unicode);
                }
            }

            // Handle mouse clicks
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (usernameField.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    setActiveField(USERNAME);
                }
                else if (passwordField.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    setActiveField(PASSWORD);
                }
                else if (loginButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    
                    // Validate credentials
                    std::string enteredUsername = inputUsername.toAnsiString(); //sfstring ot std string
                    std::string enteredPassword = inputPassword.toAnsiString();


                    if (users.find(enteredUsername) != users.end() &&
                        std::get<0>(users[enteredUsername]) == enteredPassword) {
                        // Successful login; update user details
                        username = enteredUsername;
                        batch = std::get<1>(users[enteredUsername]);
                        major = std::get<2>(users[enteredUsername]);


                        AuthScreen::showDialogBox(window, "Login successful! Welcome, " + username + ".", "Success");
                        return true;
                    }
                    else
                    {
                        AuthScreen::showDialogBox(window, "Invalid credentials. Please try again.", "Error");
                    }
                }
                else if (signupButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    // Switch to signup screen
                    signupScreen(window, filePath);
                    if (!User::loadUsersWithDetails(filePath, users)) {
                        AuthScreen::showDialogBox(window, "Error refreshing user data.", "Error");
                    }
                }
            }
        }

        // Update text
        usernameText.setString(inputUsername);
        passwordText.setString(std::string(inputPassword.getSize(), '*')); // Mask password input

        // Render UI
        window.clear(sf::Color::White);

        window.draw(title);
        window.draw(usernameLabel);
        window.draw(passwordLabel);
        window.draw(usernameField);
        window.draw(passwordField);
        window.draw(usernameText);
        window.draw(passwordText);
        window.draw(loginButton);
        window.draw(loginButtonText);
        window.draw(signupButton);
        window.draw(signupButtonText);

        window.display();
    }

    return false;
}

void AuthScreen::signupScreen(sf::RenderWindow& window, const std::string& filePath) {
    sf::Font font;
    if (!font.loadFromFile("F:\\sem3\\OOP\\oop-project\\src\\Marketplace\\Arial.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return;
    }
    std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> users;
    User::loadUsersWithDetails(filePath, users);

    

    // UI Elements
    sf::Text title("Signup", font, 30);
    title.setPosition(150, 20);
    title.setFillColor(sf::Color::Black);

    // Labels
    sf::Text usernameLabel("Username:", font, 15);
    usernameLabel.setPosition(50, 80);
    usernameLabel.setFillColor(sf::Color::Black);

    sf::Text passwordLabel("Password:", font, 15);
    passwordLabel.setPosition(50, 130);
    passwordLabel.setFillColor(sf::Color::Black);

    sf::Text batchLabel("Batch:", font, 15);
    batchLabel.setPosition(50, 180);
    batchLabel.setFillColor(sf::Color::Black);

    sf::Text majorLabel("Major:", font, 15);
    majorLabel.setPosition(50, 230);
    majorLabel.setFillColor(sf::Color::Black);

    // Input fields
    sf::RectangleShape usernameField(sf::Vector2f(200, 25));
    usernameField.setPosition(150, 80);
    usernameField.setFillColor(sf::Color(230, 230, 230));

    sf::RectangleShape passwordField(sf::Vector2f(200, 25));
    passwordField.setPosition(150, 130);
    passwordField.setFillColor(sf::Color(230, 230, 230));

    sf::RectangleShape batchField(sf::Vector2f(200, 25));
    batchField.setPosition(150, 180);
    batchField.setFillColor(sf::Color(230, 230, 230));

    sf::RectangleShape majorField(sf::Vector2f(200, 25));
    majorField.setPosition(150, 230);
    majorField.setFillColor(sf::Color(230, 230, 230));

    // Buttons
    sf::RectangleShape signupButton(sf::Vector2f(100, 30));
    signupButton.setPosition(150, 280);
    signupButton.setFillColor(sf::Color::Blue);

    sf::Text signupButtonText("Signup", font, 15);
    signupButtonText.setPosition(175, 285);
    signupButtonText.setFillColor(sf::Color::White);

    sf::RectangleShape backButton(sf::Vector2f(100, 30));
    backButton.setPosition(150, 330);
    backButton.setFillColor(sf::Color::Red);

    sf::Text backButtonText("Back", font, 15);
    backButtonText.setPosition(180, 335);
    backButtonText.setFillColor(sf::Color::White);

    // Input handling variables
    sf::String inputUsername, inputPassword, inputBatch, inputMajor;
    sf::Text usernameText("", font, 15);
    usernameText.setPosition(155, 85);
    usernameText.setFillColor(sf::Color::Black);

    sf::Text passwordText("", font, 15);
    passwordText.setPosition(155, 135);
    passwordText.setFillColor(sf::Color::Black);

    sf::Text batchText("", font, 15);
    batchText.setPosition(155, 185);
    batchText.setFillColor(sf::Color::Black);

    sf::Text majorText("", font, 15);
    majorText.setPosition(155, 235);
    majorText.setFillColor(sf::Color::Black);

    // Active field management
    enum ActiveField { NONE, USERNAME, PASSWORD, BATCH, MAJOR };
    ActiveField activeField = NONE;

    auto setActiveField = [&](ActiveField field) {
        activeField = field;
        usernameField.setFillColor(sf::Color(230, 230, 230));
        passwordField.setFillColor(sf::Color(230, 230, 230));
        batchField.setFillColor(sf::Color(230, 230, 230));
        majorField.setFillColor(sf::Color(230, 230, 230));

        if (activeField == USERNAME) usernameField.setFillColor(sf::Color::White);
        if (activeField == PASSWORD) passwordField.setFillColor(sf::Color::White);
        if (activeField == BATCH) batchField.setFillColor(sf::Color::White);
        if (activeField == MAJOR) majorField.setFillColor(sf::Color::White);
    };
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            // Handle text input
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Handle backspace
                    if (activeField == USERNAME && !inputUsername.isEmpty())
                        inputUsername.erase(inputUsername.getSize() - 1, 1);
                    else if (activeField == PASSWORD && !inputPassword.isEmpty())
                        inputPassword.erase(inputPassword.getSize() - 1, 1);
                    else if (activeField == BATCH && !inputBatch.isEmpty())
                        inputBatch.erase(inputBatch.getSize() - 1, 1);
                    else if (activeField == MAJOR && !inputMajor.isEmpty())
                        inputMajor.erase(inputMajor.getSize() - 1, 1);
                } else if (event.text.unicode < 128) { // Handle normal input
                    if (activeField == USERNAME)
                        inputUsername += static_cast<char>(event.text.unicode);
                    else if (activeField == PASSWORD)
                        inputPassword += static_cast<char>(event.text.unicode);
                    else if (activeField == BATCH)
                        inputBatch += static_cast<char>(event.text.unicode);
                    else if (activeField == MAJOR)
                        inputMajor += static_cast<char>(event.text.unicode);
                }
            }

            // Handle mouse clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (usernameField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    setActiveField(USERNAME);
                } else if (passwordField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    setActiveField(PASSWORD);
                } else if (batchField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    setActiveField(BATCH);
                } else if (majorField.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    setActiveField(MAJOR);
                } else if (signupButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Attempt signup
                    std::string username = inputUsername.toAnsiString();
                    std::string password = inputPassword.toAnsiString();
                    std::string batch = inputBatch.toAnsiString();
                    std::string major = inputMajor.toAnsiString();

                    if (username.empty() || password.empty() || batch.empty() || major.empty()) {
                        AuthScreen::showDialogBox(window, "Please fill in all fields!", "Error");
                    }else if (users.find(username) != users.end()) {
                        AuthScreen::showDialogBox(window, "Username already exists", "Error");
                    }  else {
                        if (User::saveUser(filePath, username, password, batch, major)) {
                          
    AuthScreen::showDialogBox(window, "Signup successful! Please log in.", "Success");
    return; // Return to login screen
} else {
    AuthScreen::showDialogBox(window, "Error saving user. Please try again.", "Error");
}

                    }
                } else if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; // Return to login screen
                }
            }
        }

        // Update text
        usernameText.setString(inputUsername);
        passwordText.setString(std::string(inputPassword.getSize(), '*')); // Mask password input
        batchText.setString(inputBatch);
        majorText.setString(inputMajor);

        // Render UI
        window.clear(sf::Color::White);

        window.draw(title);
        window.draw(usernameLabel);
        window.draw(passwordLabel);
        window.draw(batchLabel);
        window.draw(majorLabel);
        window.draw(usernameField);
        window.draw(passwordField);
        window.draw(batchField);
        window.draw(majorField);
        window.draw(usernameText);
        window.draw(passwordText);
        window.draw(batchText);
        window.draw(majorText);
        window.draw(signupButton);
        window.draw(signupButtonText);
        window.draw(backButton);
        window.draw(backButtonText);

        window.display();
    }
}

void AuthScreen::showProfileScreen(sf::RenderWindow& window, const std::string& username, const std::string& batch, const std::string& major) {
    sf::Font font;
    if (!font.loadFromFile("F:\\sem3\\OOP\\oop-project\\src\\Marketplace\\Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    sf::Text title("My Profile", font, 30);
    title.setPosition(300, 20);
    title.setFillColor(sf::Color::Black);

    sf::Text usernameText("Name: " + username, font, 20);
    usernameText.setPosition(100, 400);
    usernameText.setFillColor(sf::Color::Black);

    sf::Text batchText("Batch: " + batch, font, 20);
    batchText.setPosition(100, 450);
    batchText.setFillColor(sf::Color::Black);


    sf::Text majorText("Major: " + major, font, 20);
    majorText.setPosition(100, 500);
    majorText.setFillColor(sf::Color::Black);

    // Profile Picture Section
    sf::RectangleShape profilePicBox(sf::Vector2f(200, 200));
    profilePicBox.setPosition(300, 100);

    sf::Texture profilePicTexture;
    bool profilePicLoaded = false;

    // Load default picture
    if (!profilePicTexture.loadFromFile("F:\\sem3\\OOP\\oop-project\\src\\Marketplace\\R.jpeg")) {
        std::cerr << "Error: Unable to load default profile picture." << std::endl;
    } else {
        profilePicBox.setTexture(&profilePicTexture);
    }

    // Text for profile picture upload
    sf::Text profilePicLabel("Click to Upload", font, 15);
    profilePicLabel.setPosition(340, 310);
    profilePicLabel.setFillColor(sf::Color::Black);

    // Back Button
    sf::RectangleShape backButton(sf::Vector2f(100, 30));
    backButton.setPosition(10, 10);
    backButton.setFillColor(sf::Color(128, 0, 128));

    sf::Text backButtonText("Back", font, 15);
    backButtonText.setPosition(35, 15);
    backButtonText.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Handle profile picture upload
                if (profilePicBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::string imagePath = openFileDialog(); // Use file dialog to select image
                    if (!imagePath.empty() && profilePicTexture.loadFromFile(imagePath)) {
                        profilePicBox.setTexture(&profilePicTexture); // Set uploaded image
                        profilePicLoaded = true;
                    } else {
                        std::cerr << "Error loading the selected image." << std::endl;
                    }
                } else if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return ; // Navigate back to the previous screen
                }
            }
        }

        // Render UI
        window.clear(sf::Color::White);

        window.draw(title);
        window.draw(usernameText);
        window.draw(batchText);
        window.draw(majorText);
        window.draw(profilePicBox);
        if (!profilePicLoaded) {
            window.draw(profilePicLabel);
        }
        window.draw(backButton);
        window.draw(backButtonText);

        window.display();
            } }