#ifndef ORDER_HPP
#define ORDER_HPP
#pragma once

#include "Trader.hpp"
#include <ctime>
#include <chrono>

using std::chrono::milliseconds;

class Order
{

    enum class Direction
    {
        BUY,
        SELL
    };

public:
    Order(Trader& trader, Direction direction, int price, int amount, milliseconds creationTime);

    int amount = 0;
    int price = 0; // in rub
    Direction direction;
    Trader trader;
    milliseconds creationTime;
};

#endif ORDER_HPP
