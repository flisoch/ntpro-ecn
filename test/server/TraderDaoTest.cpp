#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "TraderDao.hpp"
#include "MemoryTraderDao.hpp"

class TraderDaoTest : public ::testing::Test
{
public:
    TraderDaoTest()
    {
        dao = std::make_unique<MemoryTraderDao>();
    }

protected:
    std::unique_ptr<TraderDao> dao;
};

TEST_F(TraderDaoTest, NewTraderIdGenerated)
{
    size_t id = dao->CreateTrader("testusername");
    ASSERT_EQ(id, 0);
}

TEST_F(TraderDaoTest, GetTraderReturnsNewTrader)
{
    size_t id = dao->CreateTrader("testusername");
    Trader* trader = dao->GetTrader(id);
    ASSERT_NE(trader, nullptr);
    ASSERT_EQ(trader->id, id);
}

TEST_F(TraderDaoTest, NewUserBalanceIsZero) {

    size_t id = dao->CreateTrader("testusername");
    Trader* trader = dao->GetTrader(id);
    ASSERT_EQ(trader->balance.rub, 0);
    ASSERT_EQ(trader->balance.usd, 0);

}

TEST_F(TraderDaoTest, UpdatedBalanceIsSaved) {

    size_t id = dao->CreateTrader("testusername");
    dao->UpdateBalance(id, 1,-60);
    auto balance = dao->GetTraderBalance(id);

    ASSERT_EQ(balance->usd, 1);
    ASSERT_EQ(balance->rub, -60);
}

TEST_F(TraderDaoTest, BalanceOfUnknownUserReturnsNoBalance) {

    auto balance = dao->GetTraderBalance(100);
    ASSERT_EQ(balance, nullptr);
}
