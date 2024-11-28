
#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>

class User {
public:
    static bool loadUsers(const std::string &filePath, std::unordered_map<std::string, std::string> &users);
    static bool saveUser(const std::string &filePath, const std::string &username, const std::string &password, const std::string &batch, const std::string &major);
    static bool loadUsersWithDetails(const std::string& filePath, std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>>& users);
};

#endif // USER_H