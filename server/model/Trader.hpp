#ifndef TRADER_HPP
#define TRADER_HPP
#pragma once

#include <string>
#include <vector>

class Order;

class Trader
{
    class Balance
    {
    public:
        long rub = 0;
        long usd = 0;
    };

public:
    Trader(std::string username);
    Trader(unsigned long id, std::string username);

    unsigned long id;
    std::string username;
    Balance balance;
    std::vector<Order> orders;
};

#endif  //TRADER_HPP
