#ifndef LIMIT_ORDER_BOOK_HPP
#define LIMIT_ORDER_BOOK_HPP

#include <vector>
#include "Order.hpp"
#include "LimitTree.hpp"

class LimitOrderBook
{
public:
    void Limit(Order *order);

    LimitTree buyLimits;
    LimitTree sellLimits;
    std::map<size_t, Order *> orders; // for cancellation

private:
    void LimitSell(Order *order);
    void LimitBuy(Order *order);
    void EraseOrder(size_t orderId);
};

#endif // LIMIT_ORDER_BOOK_HPP
