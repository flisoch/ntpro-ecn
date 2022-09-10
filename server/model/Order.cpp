#include "Order.hpp"

Order::Order(size_t traderId, Direction direction, double price, double amount/*, milliseconds creationTime*/)
    : traderId(traderId),
      direction(direction),
      price(price),
      amount(amount)/*,
      creationTime(creationTime)*/
{
}
