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
    // std::string traderId = json["TraderId"];
    return OrderDTO(
        json["TraderId"],
        json["Direction"],
        json["Price"],
        json["Amount"]);
}
