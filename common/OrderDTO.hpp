#ifndef ORDER_DTO_HPP
#define ORDER_DTO_HPP
#pragma once

#include <string>
#include "json.hpp"
#include "Order.hpp"

class Order;
class OrderDTO
{

public:
    OrderDTO(size_t traderId, std::string direction, double price, double amount);

    nlohmann::json toJson();
    static OrderDTO fromJson(nlohmann::json json);
    static OrderDTO fromOrder(Order order);
    std::string toString();

    double amount = 0; // usd
    double price = 0;  // rub
    std::string direction;
    size_t traderId;
};

#endif // ORDER_DTO_HPP
