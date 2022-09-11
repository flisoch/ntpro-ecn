#ifndef LIMIT_TREE_HPP
#define LIMIT_TREE_HPP
#pragma once

#include <map>
#include <functional>
#include "Limit.hpp"

class LimitTree
{

public:
    struct MyCompare
    {
        MyCompare(bool useLess) : useLess_(useLess) {}
        bool operator()(size_t lhs, size_t rhs) const
        {
            if (useLess_)
            {
                return (lhs < rhs);
            }
            else
            {
                return (lhs > rhs);
            }
        }
        bool useLess_;
    };

    LimitTree(MyCompare comparator);
    void NewLimit(Order *order); // new Limit, used if Can't fill/execute order instantly

    void Market(Order *order, std::function<void(size_t)> onFill); // try to fill order
    std::map<double, Limit *, MyCompare> limits;                   // price to limits map

private:
    bool Matched(double limit, double market, Order::Direction direction);
    void Finish(Order *order);
};

#endif // LIMIT_TREE_HPP
