#include <string>

#include "gtest/gtest.h"
#include "Core.hpp"
#include "Server.hpp"
#include "Common.hpp"

class ShowBalanceTest : public ::testing::Test
{
protected:
	Core core;
    std::string status;
};

TEST_F(ShowBalanceTest, NewUserBalanceIsZero) {

    size_t id = core.RegisterNewUser("testuser", status);
    std::string balance = core.GetTraderBalance(id, status);
    ASSERT_EQ(balance, "USD:0, RUB:0");
}

TEST_F(ShowBalanceTest, ChangedBalanceIsSaved) {

    size_t id = core.RegisterNewUser("testuser", status);
    Trader* trader = core.GetTrader(id);
    trader->balance.rub = -60;
    trader->balance.usd = 1;

    std::string balance = core.GetTraderBalance(id, status);

    ASSERT_EQ(balance, "USD:1, RUB:-60");
}

TEST_F(ShowBalanceTest, BalanceOfUnknownUserReturnsNoBalance) {

    std::string balance = core.GetTraderBalance(1, status);

    ASSERT_EQ(balance, "");
    ASSERT_EQ(status, StatusCodes::UserNotFound);
}
