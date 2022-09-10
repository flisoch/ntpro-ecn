#ifndef LIMIT_ORDER_BOOK_HPP
#define LIMIT_ORDER_BOOK_HPP


#include <vector>
#include "Order.hpp"
#include "LimitTree.hpp"

class LimitOrderBook
{
public:
    void Limit(Order order);

private:
    void LimitSell(Order order);
    void LimitBuy(Order order);

    LimitTree<Order::Direction::BUY> buyLimits;
    LimitTree<Order::Direction::SELL> sellLimits;
    std::vector<Order> orders; // for cancellation
};

#endif // LIMIT_ORDER_BOOK_HPP
