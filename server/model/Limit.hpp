#ifndef LIMIT_HPP
#define LIMIT_HPP
#pragma once

#include <chrono>
#include <memory>
#include <map>
#include "Order.hpp"

class Limit
{

public:

    Limit(Order order);
    double price;
    double volume; //total amount of usd for this price
    std::map<double, Order> ordersTree; // sorted by price
};

#endif // LIMIT_HPP
