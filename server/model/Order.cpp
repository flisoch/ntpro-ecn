#include "Order.hpp"

Order::Order(size_t traderId, Direction direction, double price, double amount)
    : traderId(traderId),
      direction(direction),
      price(price),
      amount(amount)
{
}

Order Order::fromDTO(OrderDTO dto) {
    Order::Direction direction = dto.direction == "sell" ? Order::Direction::BUY: Order::Direction::SELL;
    return Order(dto.traderId, direction, dto.price, dto.amount);
}
