#ifndef USER_H
#define USER_H
#pragma once

#include <string>
#include <vector>
#include "Order.hpp"

class Trader
{
    class Balance
    {
    public:
        long rub = 0;
        long usd = 0;
    };

public:
    Trader(std::string username) : username(username) {}
    Trader(unsigned long id, std::string username)
        : id(id),
          username(username)
    {
    }

    unsigned long id;
    std::string username;
    Balance balance;
    std::vector<Order> orders;
};

#endif
