#ifndef ORDER_HPP
#define ORDER_HPP
#pragma once

#include <chrono>
#include <memory>

using std::chrono::milliseconds;

class Order
{

public:
    enum class Direction : bool
    {
        BUY = true,
        SELL = false
    };
    Order() = default;
    Order(size_t traderId, Direction direction, double price, double amount/*, milliseconds creationTime*/);
    size_t orderId;
    double amount = 0; // usd
    double price = 0;  // rub
    Direction direction;
    size_t traderId;
    // milliseconds creationTime;
};

#endif // ORDER_HPP
