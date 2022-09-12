#include "Trader.hpp"

Trader::Trader(size_t id, std::string username)
    : id(id),
      username(username) {}

Trader::Trader(std::string username)
    : username(username) {}
    