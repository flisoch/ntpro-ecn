#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "MemoryOrderDao.hpp"

class OrderDaoTest : public ::testing::Test
{
public:
    OrderDaoTest()
    {
        dao = std::make_unique<MemoryOrderDao>();
    }

protected:
    std::unique_ptr<OrderDao> dao;
};

TEST_F(OrderDaoTest, NewOrderIdGenerated)
{   
    size_t traderId = 0;

    Order order = Order(traderId, Order::Direction::BUY, 60, 1);
    size_t id = dao->AddOrder(order);
    ASSERT_EQ(id, 0);
}

