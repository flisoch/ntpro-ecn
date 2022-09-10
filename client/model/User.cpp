#include "User.hpp"

User::User(size_t id, std::string username)
    : id(id),
      username(username) {}

User::User(std::string username)
    : username(username) {}
    