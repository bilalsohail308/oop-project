#include "User.hpp"
#include <sstream>
#include<vector>

User::User(const std::string& username, const std::string& password, 
           const std::string& batch, const std::string& major, 
           const std::string& profilePicture)
    : username(username), password(password), batch(batch), major(major), profilePicture(profilePicture) {}

std::string User::toString() const {
    return username + "," + password + "," + batch + "," + major + "," + profilePicture;
}

User User::fromString(const std::string& data) {
    std::istringstream ss(data);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 2) {
        throw std::runtime_error("Invalid user data format");
    }

    return User(
        tokens[0], // username
        tokens[1], // password
        tokens.size() > 2 ? tokens[2] : "",  // batch
        tokens.size() > 3 ? tokens[3] : "",  // major
        tokens.size() > 4 ? tokens[4] : ""   // profilePicture
    );
}
