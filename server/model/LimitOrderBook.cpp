
#include "LimitOrderBook.hpp"

void LimitOrderBook::Limit(Order order)
{
    order.orderId = orders.size();
    orders.push_back(order);

    if (order.direction == Order::Direction::BUY)
    {
        LimitBuy(order);
    }
    else if (order.direction == Order::Direction::SELL)
    {
        LimitSell(order);
    }
}

void LimitOrderBook::LimitSell(Order order)
{
    if (!buyLimits.limits.empty() && order.price <= buyLimits.limits.begin()->first)
    {
        buyLimits.Market(&orders[order.orderId]);
        if (orders[order.orderId].amount == 0) {
            orders.erase(orders.begin() + order.orderId);
        }
    }
    sellLimits.NewLimit(&orders[order.orderId]);
}
void LimitOrderBook::LimitBuy(Order order)
{

    if (!sellLimits.limits.empty() && order.price >= sellLimits.limits.begin()->first)
    {
        sellLimits.Market(&orders[order.orderId]);
        if (orders[order.orderId].amount == 0) {
            orders.erase(orders.begin() + order.orderId);
        }
    }
    sellLimits.NewLimit(&orders[order.orderId]);
}
