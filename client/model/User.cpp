#include "User.hpp"

User::User(unsigned long id, std::string username)
    : id(id),
      username(username) {}

User::User(std::string username)
    : username(username) {}
    