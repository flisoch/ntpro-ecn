#ifndef LIMIT_TREE_HPP
#define LIMIT_TREE_HPP
#pragma once

#include <memory>
#include <map>
#include "Limit.hpp"

template<Order::Direction direction>
class LimitTree
{

public:
    LimitTree();

    double volume;                      // total amount of usd for this tree
    std::map<double, Limit> limits;     // price to limits map

    void Limit(Order* order); // new Limit, used if Can't fill/execute order instantly
    bool Market(Order* order); // try to fill order
    void Finish(Order* order); // remove order from limit tree
};

#endif // LIMIT_TREE_HPP
