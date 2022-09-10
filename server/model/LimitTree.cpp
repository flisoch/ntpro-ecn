
#include "LimitTree.hpp"

LimitTree::LimitTree()
{
}

void LimitTree::NewLimit(Order *order)
{
    if (limits.find(order->price) == limits.end())
    {
        Limit *limit = new Limit(order);
        order->limit = limit;
        limits.emplace(order->price, limit);
    }
    else
    {
        Limit *limit = limits.at(order->price);
        limit->orders.push_back(order);
        order->limit = limit;
        order->limit->volume += order->amount;
    }
}

void LimitTree::Market(Order *order, std::function<void(size_t)> onFill)
{
    while (Matched(limits.begin()->first, order->price, order->direction))
    {
        Order *matchedOrder = limits.begin()->second->orders.front();
        if (matchedOrder->amount >= order->amount)
        {
            if (matchedOrder->amount == order->amount)
            {
                Finish(matchedOrder);
                onFill(matchedOrder->orderId);
            }
            else
            {
                matchedOrder->amount -= order->amount;
                matchedOrder->limit->volume -= order->amount;
            }
            onFill(order->orderId);
            return;
        }
        order->amount -= matchedOrder->amount;
        Finish(matchedOrder);
        onFill(matchedOrder->orderId);
    }
}
void LimitTree::Finish(Order *order)
{
    auto limit = order->limit;
    if (limit->orders.size() == 1)
    {
        limits.erase(limit->price);
    }
    else
    {
        limit->volume -= order->amount;
        limit->orders.pop_back();
    }
}

bool LimitTree::Matched(double limit, double market, Order::Direction direction)
{
    switch (direction)
    {
    case Order::Direction::SELL:
        return limit <= market;
        break;
    case Order::Direction::BUY:
        return limit >= market;
        break;
    default:
        break;
    }
    return false;
}
