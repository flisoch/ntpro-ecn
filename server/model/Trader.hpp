#ifndef TRADER_HPP
#define TRADER_HPP
#pragma once

#include <string>
#include <vector>
#include "Order.hpp"

class Trader
{

public:
    class Balance
    {
    public:
        long rub = 0;
        long usd = 0;
    };

    Trader(std::string username);
    Trader(size_t id, std::string username);

    size_t id;
    std::string username;
    Balance balance;
    // std::map<size_t, Order *> orders;
};

#endif // TRADER_HPP
