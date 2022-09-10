#ifndef ORDER_DAO_HPP
#define ORDER_DAO_HPP

#include <vector>
#include "Order.hpp"

class OrderDao
{
public:
    virtual std::vector<Order> GetOrdersByTraderId(size_t id) = 0;
    virtual size_t AddOrder(Order order) = 0;
    virtual void DeleteOrder(size_t orderId) = 0;
    virtual void UpdateOrder(Order order) = 0;
};

#endif // ORDER_DAO_HPP
