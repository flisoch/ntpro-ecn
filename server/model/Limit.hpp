#ifndef LIMIT_HPP
#define LIMIT_HPP
#pragma once

#include <chrono>
#include <memory>
#include <vector>
#include "Order.hpp"

class Order;

class Limit
{

public:

    Limit(Order* order);
    double price = 0;
    double volume = 0; //total amount of usd for this price
    std::vector<Order*> orders; // FIFO
};

#endif // LIMIT_HPP
