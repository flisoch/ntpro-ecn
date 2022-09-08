#include "Order.hpp"

Order::Order(unsigned long traderId, Direction direction, int price, int amount, milliseconds creationTime)
    : traderId(traderId),
      direction(direction),
      price(price),
      amount(amount),
      creationTime(creationTime)
{
}
