#include <string>

#include "gtest/gtest.h"
#include "LimitOrderBook.hpp"
#include "MemoryTraderDao.hpp"
#include <memory>

class OrderBookTest : public ::testing::Test
{
public:
    OrderBookTest()
    {   
        traderDao = std::make_shared<MemoryTraderDao>();
        orderBook.traderDao = traderDao;

        traderDao->CreateTrader("dummy");
        traderDao->CreateTrader("dummyOpposite");

        dummyOrder = Order(0, Order::Direction::BUY, 60, 1);
        dummyOpposite = Order(1, Order::Direction::SELL, 60, 1);
    }

protected:
    LimitOrderBook orderBook;
    std::shared_ptr<TraderDao> traderDao;
    Order dummyOrder;
    Order dummyOpposite;
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
    orderBook.Limit(&dummyOpposite);

    ASSERT_EQ(orderBook.orders.empty(), 1);
    ASSERT_EQ(orderBook.buyLimits.limits.empty(), 1);
    ASSERT_EQ(orderBook.sellLimits.limits.empty(), 1);
}

TEST_F(OrderBookTest, OneFillsTwo)
{
    dummyOpposite.amount = 2;
    traderDao->CreateTrader("testname");
    Order dummyCopy = Order(0, Order::Direction::BUY, 60, 1);
    orderBook.Limit(&dummyOrder);
    orderBook.Limit(&dummyCopy);
    orderBook.Limit(&dummyOpposite);

    ASSERT_EQ(orderBook.buyLimits.limits.empty(), 1);
    ASSERT_EQ(orderBook.sellLimits.limits.empty(), 1);
    ASSERT_EQ(orderBook.orders.empty(), 1);
}

TEST_F(OrderBookTest, TwoOppositesAndOneLeftsOne)
{
    traderDao->CreateTrader("test1");
    traderDao->CreateTrader("test2");
    traderDao->CreateTrader("test3");
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
    traderDao->CreateTrader("test1");
    traderDao->CreateTrader("test2");
    traderDao->CreateTrader("test3");
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
    traderDao->CreateTrader("test1");
    traderDao->CreateTrader("test2");
    traderDao->CreateTrader("test3");
    Order order1 = Order(1, Order::Direction::SELL, 61, 1);
    Order order2 = Order(2, Order::Direction::SELL, 60, 1);
    Order order3 = Order(3, Order::Direction::BUY, 63, 2);

    orderBook.Limit(&order1);
    orderBook.Limit(&order2);
    orderBook.Limit(&order3);

    ASSERT_EQ(orderBook.buyLimits.limits.size(), 0);
    ASSERT_EQ(orderBook.sellLimits.limits.size(), 0);
    ASSERT_EQ(orderBook.orders.size(), 0);
}

TEST_F(OrderBookTest, BuyLimitsInDescendingOrder)
{
    traderDao->CreateTrader("test1");
    traderDao->CreateTrader("test2");

    Order order1 = Order(1, Order::Direction::BUY, 63, 1);
    Order order2 = Order(2, Order::Direction::BUY, 62, 1);

    orderBook.Limit(&order1);
    orderBook.Limit(&order2);
    bool firstIsGreater = orderBook.buyLimits.limits.begin()->first > std::next(orderBook.buyLimits.limits.begin())->first;

    ASSERT_EQ(firstIsGreater, 1);
}

TEST_F(OrderBookTest, BalanceUpdatedCorrectly)
{
    size_t id1 = traderDao->CreateTrader("test1");
    size_t id2 = traderDao->CreateTrader("test2");
    size_t id3 = traderDao->CreateTrader("test3");
    auto trader1 = traderDao->GetTrader(id1);
    auto trader2 = traderDao->GetTrader(id2);
    auto trader3 = traderDao->GetTrader(id3);


    Order order1 = Order(id1, Order::Direction::BUY, 62, 10);
    Order order2 = Order(id2, Order::Direction::BUY, 63, 20);
    Order order3 = Order(id3, Order::Direction::SELL, 61, 50);

    orderBook.Limit(&order1);
    orderBook.Limit(&order2);
    orderBook.Limit(&order3);

    ASSERT_EQ(orderBook.orders.size(), 1);
    ASSERT_EQ(orderBook.orders.begin()->second->amount, 20);
    ASSERT_EQ(trader1->balance.rub, -620);
    ASSERT_EQ(trader1->balance.usd, 10);
    ASSERT_EQ(trader2->balance.rub, -1260);
    ASSERT_EQ(trader2->balance.usd, 20);
    ASSERT_EQ(trader3->balance.rub, 1880);
    ASSERT_EQ(trader3->balance.usd, -50);
}

TEST_F(OrderBookTest, NotFilledOrderCanBeFilledLater)
{
    size_t id1 = traderDao->CreateTrader("test1");
    size_t id2 = traderDao->CreateTrader("test2");
    auto trader1 = traderDao->GetTrader(id1);
    auto trader2 = traderDao->GetTrader(id2);


    Order order1 = Order(id1, Order::Direction::BUY, 60, 10);
    Order order2 = Order(id2, Order::Direction::SELL, 60, 20);
    orderBook.Limit(&order1);
    orderBook.Limit(&order2);
    Order order3 = Order(id1, Order::Direction::BUY, 60, 10);
    orderBook.Limit(&order3);

    ASSERT_EQ(orderBook.orders.size(), 0);
    ASSERT_EQ(trader1->balance.rub, -1200);
    ASSERT_EQ(trader1->balance.usd, 20);
    ASSERT_EQ(trader2->balance.rub, 1200);
    ASSERT_EQ(trader2->balance.usd, -20);
}