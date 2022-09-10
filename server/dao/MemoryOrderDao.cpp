#include "MemoryOrderDao.hpp"

std::vector<Order> MemoryOrderDao::GetOrdersByTraderId(size_t id) {
    return {};
}
size_t MemoryOrderDao::AddOrder(Order newOrder) {
    if (newOrder.direction == Order::Direction::BUY) {
        buyOrders.push_back(newOrder);
    }
    else if (newOrder.direction == Order::Direction::SELL) {
        sellOrders.push_back(newOrder);
    }
    return buyOrders.size() - 1;
}
void MemoryOrderDao::DeleteOrder(size_t orderId) {
    
}
void MemoryOrderDao::UpdateOrder(Order updatedOrder) {

}
