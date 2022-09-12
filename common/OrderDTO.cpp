#include "OrderDTO.hpp"

OrderDTO::OrderDTO(size_t traderId, std::string direction, double price, double amount)
    : traderId(traderId),
      direction(direction),
      price(price),
      amount(amount)
{
}

nlohmann::json OrderDTO::toJson()
{
    nlohmann::json message;
    message["TraderId"] = traderId;
    message["Direction"] = direction;
    message["Price"] = price;
    message["Amount"] = amount;
    return message;
}

OrderDTO OrderDTO::fromJson(nlohmann::json json)
{
    return OrderDTO(
        json["TraderId"],
        json["Direction"],
        json["Price"],
        json["Amount"]);
}
OrderDTO OrderDTO::fromOrder(Order order)
{
    std::string direction = order.direction == Order::Direction::SELL ? "sell" : "buy";
    return OrderDTO(order.traderId, direction, order.price, order.amount);
}

std::string OrderDTO::toString()
{
    std::string order =
        "TraderId: " + std::to_string(traderId) + "\n" +
        "Direction: " + direction + "\n" +
        "Price " + std::to_string(price) + "\n" +
        "Amount " + std::to_string(amount) + "\n";

    return order;
}
