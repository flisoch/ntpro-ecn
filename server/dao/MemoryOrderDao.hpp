#include "OrderDao.hpp"

class MemoryOrderDao : public OrderDao
{
public:
    std::vector<Order> GetOrdersByTraderId(size_t id) override;
    size_t AddOrder(Order newOrder) override;
    void DeleteOrder(size_t orderId) override;
    void UpdateOrder(Order updatedOrder) override;
private:
    std::vector<Order> sellOrders;
    std::vector<Order> buyOrders;
};