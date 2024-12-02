#include "../include/User.h"
#include <fstream>
#include <sstream>
#include <iostream>
//key=username
//value=tuple
bool User::loadUsers(const std::string& filePath, std::unordered_map<std::string, std::string>& users) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open users file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line); //taking input line by line and splitting it based on whitespaces
        std::string username, password, batch, major;

     
        if (std::getline(ss, username, ',') && std::getline(ss, password, ',') &&
            std::getline(ss, batch, ',') && std::getline(ss, major)) {
            
            
            username.erase(username.find_last_not_of(" \n\r\t") + 1); //trim whitespaces
            username.erase(0, username.find_first_not_of(" \n\r\t"));
            password.erase(password.find_last_not_of(" \n\r\t") + 1);
            password.erase(0, password.find_first_not_of(" \n\r\t"));

            
            users[username] = password;  // Store username and password in the map

            
            std::cout << "Loaded user: [" << username << "] with password: [" << password << "]" << std::endl; 
        }
    }

    file.close();
    return true;
}

bool User::saveUser(const std::string& filePath, const std::string& username, const std::string& password, const std::string& batch, const std::string& major) {
    std::ofstream file(filePath, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to write to users file." << std::endl;
        return false;
    }

    // Write all fields to the file
    file << username << "," << password << "," << batch << "," << major << "\n";

    file.close();
    return true;
}
bool User::loadUsersWithDetails(const std::string& filePath, std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>>& users) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open users file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string username, password, batch, major;

        if (std::getline(ss, username, ',') && std::getline(ss, password, ',') && 
            std::getline(ss, batch, ',') && std::getline(ss, major)) {
            users[username] = std::make_tuple(password, batch, major);
        }  //Extracts each field from the line, separated by commas 
    }

    file.close();
    return true;
}