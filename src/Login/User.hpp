#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string password;
    std::string batch;
    std::string major;
    std::string profilePicture;

    
    User(const std::string& username, const std::string& password, 
         const std::string& batch = "", const std::string& major = "", 
         const std::string& profilePicture = "");

    
    std::string toString() const;

   
    static User fromString(const std::string& data);
};

#endif // USER_H
