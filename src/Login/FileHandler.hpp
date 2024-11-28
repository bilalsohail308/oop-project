#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include "User.hpp"

class FileHandler {
public:
    // Loads all users from the specified file
    static std::vector<User> loadUsers(const std::string& filePath);

    // Saves the list of users to the specified file
    static void saveUsers(const std::string& filePath, const std::vector<User>& users);

    // Checks if a username already exists in the file
    static bool userExists(const std::string& filePath, const std::string& username);
};

#endif // FILE_HANDLER_H
