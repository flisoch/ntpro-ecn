#ifndef LIMIT_TREE_HPP
#define LIMIT_TREE_HPP
#pragma once

#include <memory>
#include <map>
#include <functional>
#include "Limit.hpp"

class LimitTree
{

public:
    LimitTree();
    void NewLimit(Order *order); // new Limit, used if Can't fill/execute order instantly

    void Market(Order *order, std::function<void(size_t)> onFill); // try to fill order
    // double volume = 0;                                             // total amount of usd for this tree
    std::map<double, Limit *> limits; // price to limits map

private:
    bool Matched(double limit, double market, Order::Direction direction);
    void Finish(Order *order);
};

#endif // LIMIT_TREE_HPP
