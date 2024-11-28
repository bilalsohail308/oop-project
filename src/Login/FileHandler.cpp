#include "FileHandler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<User> FileHandler::loadUsers(const std::string& filePath) {
    std::vector<User> users;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                users.push_back(User::fromString(line));
            } catch (const std::exception& e) {
                std::cerr << "Error parsing user data: " << e.what() << std::endl;
            }
        }
    }

    file.close();
    return users;
}

void FileHandler::saveUsers(const std::string& filePath, const std::vector<User>& users) {
    std::ofstream file(filePath, std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filePath << std::endl;
        return;
    }

    for (const auto& user : users) {
        file << user.toString() << std::endl;
    }

    file.close();
}

bool FileHandler::userExists(const std::string& filePath, const std::string& username) {
    auto users = loadUsers(filePath);
    for (const auto& user : users) {
        if (user.username == username) {
            return true;
        }
    }
    return false;
}
