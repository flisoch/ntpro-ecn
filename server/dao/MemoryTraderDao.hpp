#ifndef MEMORY_TRADER_DAO_HPP
#define MEMORY_TRADER_DAO_HPP

#include "TraderDao.hpp"

class MemoryTraderDao : public TraderDao
{
public:
    Trader *GetTrader(size_t traderId) override;
    Trader *GetTraderByUsername(std::string username) override;

    Trader::Balance *GetTraderBalance(size_t traderId) override;
    size_t CreateTrader(std::string username) override;
    Trader::Balance *UpdateBalance(size_t traderId, int usd, int rub) override;
    size_t Size() const override;

private:
    std::vector<Trader> traders;
};

#endif // MEMORY_TRADER_DAO_HPP
