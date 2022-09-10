#ifndef ORDER_HPP
#define ORDER_HPP
#pragma once

#include "Limit.hpp"

class Limit;

class Order
{

public:
    enum class Direction : bool
    {
        BUY = true,
        SELL = false
    };

    Order() = default;
    Order(size_t traderId, Direction direction, double price, double amount);
    size_t orderId;
    double amount = 0; // usd
    double price = 0;  // rub
    Direction direction;
    size_t traderId;
    Limit* limit = nullptr;
};

#endif // ORDER_HPP
