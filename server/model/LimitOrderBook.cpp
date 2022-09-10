
#include "LimitOrderBook.hpp"

void LimitOrderBook::Limit(Order *order)
{
    order->orderId = orders.size();
    orders.emplace(order->orderId, order);

    if (order->direction == Order::Direction::BUY)
    {
        LimitBuy(order);
    }
    else if (order->direction == Order::Direction::SELL)
    {
        LimitSell(order);
    }
}

void LimitOrderBook::LimitSell(Order *order)
{
    if (!buyLimits.limits.empty() && order->price <= buyLimits.limits.begin()->first)
    {
        buyLimits.Market(orders[order->orderId],
                         [&](size_t id)
                         { orders.erase(id); });
    }
    else
    {
        sellLimits.NewLimit(orders[order->orderId]);
    }
}
void LimitOrderBook::LimitBuy(Order *order)
{

    if (!sellLimits.limits.empty() && order->price >= sellLimits.limits.begin()->first)
    {
        sellLimits.Market(orders[order->orderId],
                          [&](size_t id)
                          { orders.erase(id); });
    }
    else
    {
        buyLimits.NewLimit(orders[order->orderId]);
    }
}

void LimitOrderBook::EraseOrder(size_t orderId)
{
    orders.erase(orderId);
}
