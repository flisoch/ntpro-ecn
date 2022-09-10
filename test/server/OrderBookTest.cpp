#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "MemoryOrderDao.hpp"
#include "LimitOrderBook.hpp"


class OrderBookTest : public ::testing::Test
{
public:
    OrderBookTest()
    {
        dummyOrder.traderId = 0;
        dummyOrder.direction = Order::Direction::BUY;
        dummyOrder.price = 60;
        dummyOrder.amount = 1;
    }

protected:
    LimitOrderBook orderBook;
    Order dummyOrder;
};

TEST_F(OrderBookTest, NewOrderInsertedIntoOrderBook)
{   

    orderBook.Limit(dummyOrder);

    ASSERT_EQ(orderBook.orders.size(), 1);
}

TEST_F(OrderBookTest, NewOrderHasCorrectId)
{   
    orderBook.Limit(dummyOrder);
    auto order = orderBook.orders[0];
    ASSERT_EQ(order.orderId, 0);
}

TEST_F(OrderBookTest, NewOrderLimitInsertedIntoLimitTree)
{   
    orderBook.Limit(dummyOrder);
    ASSERT_EQ(orderBook.buyLimits.limits.empty(), 0);
}