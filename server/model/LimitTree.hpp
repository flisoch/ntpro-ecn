#ifndef LIMIT_TREE_HPP
#define LIMIT_TREE_HPP
#pragma once

#include <memory>
#include <map>
#include "Limit.hpp"

class LimitTree
{

public:
    LimitTree();
    void NewLimit(Order *order); // new Limit, used if Can't fill/execute order instantly
    void Market(Order *order);   // try to fill order
    void Finish(Order *order);   // remove order from limit tree

    double volume = 0;                  // total amount of usd for this tree
    std::map<double, Limit> limits; // price to limits map
};

#endif // LIMIT_TREE_HPP
