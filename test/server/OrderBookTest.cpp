#include <string>

#include "gtest/gtest.h"
#include "LimitOrderBook.hpp"
#include <memory>

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

TEST_F(OrderBookTest, OneFillsTwo)
{
    Order order1 = Order(0, Order::Direction::BUY, 60, 1);
    Order order2 = Order(1, Order::Direction::BUY, 60, 1);
    Order order3 = Order(2, Order::Direction::SELL, 60, 2);

    orderBook.Limit(&order1);
    orderBook.Limit(&order2);
    orderBook.Limit(&order3);

    ASSERT_EQ(orderBook.buyLimits.limits.empty(), 1);
    ASSERT_EQ(orderBook.sellLimits.limits.empty(), 1);
    ASSERT_EQ(orderBook.orders.empty(), 1);
}

TEST_F(OrderBookTest, TwoOppositesAndOneLeftsOne)
{
    Order order1 = Order(0, Order::Direction::BUY, 60, 2);
    Order order2 = Order(1, Order::Direction::BUY, 60, 1);
    Order order3 = Order(2, Order::Direction::SELL, 60, 2);

    orderBook.Limit(&order1);
    orderBook.Limit(&order2);
    orderBook.Limit(&order3);

    ASSERT_EQ(orderBook.buyLimits.limits.size(), 1);
    ASSERT_EQ(orderBook.sellLimits.limits.empty(), 1);
    ASSERT_EQ(orderBook.orders.size(), 1);

}

TEST_F(OrderBookTest, LateOrderFillsPartially)
{
    Order order1 = Order(0, Order::Direction::BUY, 60, 1);
    Order order2 = Order(1, Order::Direction::BUY, 60, 2);
    Order order3 = Order(2, Order::Direction::SELL, 60, 2);

    orderBook.Limit(&order1);
    orderBook.Limit(&order2);
    orderBook.Limit(&order3);

    EXPECT_EQ(orderBook.buyLimits.limits.size(), 1);
    EXPECT_EQ(orderBook.sellLimits.limits.empty(), 1);
    EXPECT_EQ(orderBook.orders.size(), 1);
    ASSERT_EQ(orderBook.orders.begin()->first, order2.orderId);
}

TEST_F(OrderBookTest, SellLimitsWithDiffPricesFilledWithOneBigBuy)
{
    Order order1 = Order(1, Order::Direction::SELL, 61, 1);
    Order order2 = Order(2, Order::Direction::SELL, 60, 1);
    Order order3 = Order(2, Order::Direction::BUY, 63, 2);

    orderBook.Limit(&order1);
    orderBook.Limit(&order2);
    orderBook.Limit(&order3);

    ASSERT_EQ(orderBook.buyLimits.limits.size(), 0);
    ASSERT_EQ(orderBook.sellLimits.limits.size(), 0);
    ASSERT_EQ(orderBook.orders.size(), 0);
}

TEST_F(OrderBookTest, BuyLimitsInDescendingOrder)
{
    Order order1 = Order(1, Order::Direction::BUY, 63, 1);
    Order order2 = Order(2, Order::Direction::BUY, 62, 1);

    orderBook.Limit(&order1);
    orderBook.Limit(&order2);
    bool firstIsGreater = orderBook.buyLimits.limits.begin()->first > std::next(orderBook.buyLimits.limits.begin())->first;

    ASSERT_EQ(firstIsGreater, 1);
}
