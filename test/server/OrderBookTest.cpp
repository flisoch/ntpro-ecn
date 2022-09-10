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
        dummyOrder = Order(0, Order::Direction::BUY, 60, 1);
    }

protected:
    LimitOrderBook orderBook;
    Order dummyOrder;
};

TEST_F(OrderBookTest, NewOrderInsertedIntoOrderBook)
{

    orderBook.Limit(&dummyOrder);

    ASSERT_EQ(orderBook.orders.size(), 1);
}

TEST_F(OrderBookTest, NewOrderHasCorrectId)
{
    orderBook.Limit(&dummyOrder);
    auto order = orderBook.orders[0];
    ASSERT_EQ(order->orderId, 0);
}

TEST_F(OrderBookTest, NewSellOrderLimitInsertedIntoLimitTree)
{
    dummyOrder.direction = Order::Direction::SELL;
    orderBook.Limit(&dummyOrder);
    ASSERT_EQ(orderBook.sellLimits.limits.empty(), 0);
}

TEST_F(OrderBookTest, NewBuyOrderLimitInsertedIntoLimitTree)
{
    orderBook.Limit(&dummyOrder);
    ASSERT_EQ(orderBook.buyLimits.limits.empty(), 0);
}

TEST_F(OrderBookTest, NewOrderHasLimitAndLimitHasOrder)
{
    orderBook.Limit(&dummyOrder);
    ASSERT_NE(orderBook.orders[0]->limit, nullptr);
    ASSERT_EQ(orderBook.buyLimits.limits[dummyOrder.price]->orders.empty(), 0);
}

TEST_F(OrderBookTest, OppositeOrderFillsLimit)
{
    orderBook.Limit(&dummyOrder);
    Order opposite = Order(1, Order::Direction::SELL, dummyOrder.price, dummyOrder.amount);
    orderBook.Limit(&opposite);

    ASSERT_EQ(orderBook.orders.empty(), 1);
    ASSERT_EQ(orderBook.buyLimits.limits.empty(), 1);
    ASSERT_EQ(orderBook.sellLimits.limits.empty(), 1);
}
