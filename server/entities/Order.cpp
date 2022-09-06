#include "Order.hpp"

Order::Order(Trader& trader, Direction direction, int price, int amount, milliseconds creationTime) 
    :
    trader(trader),
    direction(direction),
    price(price),
    amount(amount),
    creationTime(creationTime)
{

}