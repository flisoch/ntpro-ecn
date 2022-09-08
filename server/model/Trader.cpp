#include "Trader.hpp"

Trader::Trader(unsigned long id, std::string username)
    : id(id),
      username(username) {}

Trader::Trader(std::string username)
    : username(username) {}
    