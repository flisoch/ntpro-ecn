#include "Order.hpp"
#include "Trader.hpp"

Order::Order(Trader &trader, Direction direction, int price, int amount, milliseconds creationTime)
    : trader(std::make_shared<Trader>(trader)),
      direction(direction),
      price(price),
      amount(amount),
      creationTime(creationTime)
{
}