#ifndef LIMIT_ORDER_BOOK_HPP
#define LIMIT_ORDER_BOOK_HPP

#include <vector>
#include "Order.hpp"
#include "LimitTree.hpp"
#include "TraderDao.hpp"

class LimitOrderBook
{
public:
    LimitOrderBook();
    
    void Limit(Order *order);

    LimitTree buyLimits;
    LimitTree sellLimits;
    std::map<size_t, Order *> orders; // for cancellation
    std::shared_ptr<TraderDao> traderDao;

private:
    void LimitSell(Order *order);
    void LimitBuy(Order *order);
    size_t serialId = 0;

};

#endif // LIMIT_ORDER_BOOK_HPP
