
#include "LimitOrderBook.hpp"

LimitOrderBook::LimitOrderBook()
    : buyLimits(LimitTree::MyCompare(false)),
      sellLimits(LimitTree::MyCompare(true))
{
}
void LimitOrderBook::Limit(Order *order)
{
    order->orderId = serialId++;
    orders.emplace(order->orderId, order);
    auto trader = traderDao->GetTrader(order->traderId);
    if (order->direction == Order::Direction::BUY)
    {
        trader->balance.rub -= order->price * order->amount;
    }
    else
    {
        trader->balance.usd -= order->amount;
    }

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
                         [&](size_t marketOrderId, size_t limitOrderId)
                         {
                             if (marketOrderId != limitOrderId)
                             {
                                 auto marketOrder = orders[marketOrderId];
                                 auto newOrder = orders[limitOrderId];
                                 auto marketTrader = traderDao->GetTrader(marketOrder->traderId);
                                 auto newTrader = traderDao->GetTrader(newOrder->traderId);

                                 if (marketOrder->direction == Order::Direction::BUY)
                                 {
                                     marketTrader->balance.usd += marketOrder->amount;
                                     newTrader->balance.rub += marketOrder->price * marketOrder->amount;
                                 }
                                 else
                                 {
                                     marketTrader->balance.rub += marketOrder->amount * marketOrder->price;
                                     newTrader->balance.usd += marketOrder->amount;
                                 }
                             }
                             orders.erase(marketOrderId);
                         });
        if (orders.find(order->orderId) != orders.end() && order->amount > 0)
        {
            sellLimits.NewLimit(order);
        }
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
                          [&](size_t marketOrderId, size_t limitOrderId)
                          {
                              if (marketOrderId != limitOrderId)
                              {
                                  auto marketOrder = orders[marketOrderId];
                                  auto newOrder = orders[limitOrderId];
                                  auto marketTrader = traderDao->GetTrader(marketOrder->traderId);
                                  auto newTrader = traderDao->GetTrader(newOrder->traderId);

                                  if (marketOrder->direction == Order::Direction::BUY)
                                  {
                                      marketTrader->balance.usd += marketOrder->amount;
                                      newTrader->balance.rub += marketOrder->price * marketOrder->amount;
                                  }
                                  else
                                  {
                                      marketTrader->balance.rub += marketOrder->amount * marketOrder->price;
                                      newTrader->balance.usd += marketOrder->amount;
                                  }
                              }
                              orders.erase(marketOrderId);
                          });
        if (orders.find(order->orderId) != orders.end() && order->amount > 0)
        {
            buyLimits.NewLimit(order);
        }
    }
    else
    {
        buyLimits.NewLimit(orders[order->orderId]);
    }
}

// void LimitOrderBook::OnFill(size_t orderId)
// {
//     orders.erase(orderId);
// }
