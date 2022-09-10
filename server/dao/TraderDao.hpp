#ifndef TRADER_DAO_HPP
#define TRADER_DAO_HPP

#include "Trader.hpp"

class TraderDao
{
public:
    virtual Trader *GetTrader(size_t traderId) = 0;
    virtual size_t CreateTrader(std::string username) = 0;
    virtual Trader::Balance *GetTraderBalance(size_t traderId) = 0;
    virtual Trader::Balance *UpdateBalance(size_t traderId, int usd, int rub) = 0;
};

#endif // TRADER_DAO_HPP
