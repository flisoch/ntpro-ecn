#ifndef ORDER_HPP
#define ORDER_HPP
#pragma once

#include <chrono>
#include <memory>

using std::chrono::milliseconds;

class Order
{

    enum class Direction
    {
        BUY,
        SELL
    };

public:
    Order(unsigned long traderId, Direction direction, int price, int amount, milliseconds creationTime);

    int amount = 0;
    int price = 0; // in rub
    Direction direction;
    unsigned long traderId;
    milliseconds creationTime;
};

#endif //ORDER_HPP
